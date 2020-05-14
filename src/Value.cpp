/**
 * @file Value.cpp
 *
 * This file contains the implementation
 * of the ClusterMemberStore::Value class.
 */

#include <ClusterMemberStore/Value.hpp>
#include <stdint.h>
#include <string>

namespace {

    using namespace ClusterMemberStore;

    union Data {
        std::string* error;
        std::string* text;
        double real;
        intmax_t integer;
        bool boolean;
    };

}

namespace ClusterMemberStore {

    struct Value::Impl {
        // Properties

        Data data;
        Type type = Type::Invalid;

        // Lifecycle
        ~Impl() noexcept {
            switch (type) {
                case Type::Text: {
                    delete data.text;
                } break;

                case Type::Error: {
                    delete data.error;
                } break;

                default: break;
            }
        }
        Impl(const Impl& other) = delete;
        Impl(Impl&& other) noexcept = default;
        Impl& operator=(const Impl& other) = delete;
        Impl& operator=(Impl&& other) noexcept = default;

        // Constructor
        Impl() = default;
    };

    Value::~Value() noexcept = default;

    Value::Value(const Value& other)
        : Value()
    {
        impl_->type = other.impl_->type;
        switch (impl_->type) {
            case Type::Boolean: {
                impl_->data.boolean = other;
            } break;

            case Type::Error: {
                impl_->data.error = new std::string(other);
            } break;

            case Type::Integer: {
                impl_->data.integer = other;
            } break;

            case Type::Real: {
                impl_->data.real = other;
            } break;

            case Type::Text: {
                impl_->data.text = new std::string(other);
            } break;

            default: break;
        }
    }

    Value::Value(Value&& other) noexcept
        : impl_(std::move(other.impl_))
    {
        other.impl_ = nullptr;
    }

    Value& Value::operator=(const Value& other) {
        if (this != &other) {
            *this = Value(other);
        }
        return *this;
    }

    Value& Value::operator=(Value&& other) noexcept {
        if (this != &other) {
            std::swap(impl_, other.impl_);
        }
        return *this;
    }

    Value::Value()
        : impl_(new Impl())
    {
    }

    Value::Value(const char* text)
        : Value(std::string(text))
    {
    }

    Value::Value(const std::string& text)
        : Value()
    {
        impl_->data.text = new std::string(text);
        impl_->type = Type::Text;
    }

    Value::Value(std::string&& text)
        : Value()
    {
        impl_->data.text = new std::string(std::move(text));
        impl_->type = Type::Text;
    }

    Value::Value(double real)
        : Value()
    {
        impl_->data.real = real;
        impl_->type = Type::Real;
    }

    Value::Value(int integer)
        : Value()
    {
        impl_->data.integer = (intmax_t)integer;
        impl_->type = Type::Integer;
    }

    Value::Value(intmax_t integer)
        : Value()
    {
        impl_->data.integer = integer;
        impl_->type = Type::Integer;
    }

    Value::Value(size_t integer)
        : Value()
    {
        impl_->data.integer = (intmax_t)integer;
        impl_->type = Type::Integer;
    }

    Value::Value(bool boolean)
        : Value()
    {
        impl_->data.boolean = boolean;
        impl_->type = Type::Boolean;
    }

    Value::Value(nullptr_t null)
        : Value()
    {
        impl_->type = Type::Null;
    }

    Value::operator const char*() const {
        static const char* defaultString = "";
        switch (impl_->type) {
            case Type::Text: return impl_->data.text->c_str();
            case Type::Error: return impl_->data.error->c_str();
            default: return defaultString;
        }
    }

    Value::operator const std::string&() const {
        static const std::string defaultString;
        switch (impl_->type) {
            case Type::Text: return *impl_->data.text;
            case Type::Error: return *impl_->data.error;
            default: return defaultString;
        }
    }

    Value::operator double() const {
        switch (impl_->type) {
            case Type::Real: return impl_->data.real;
            default: return 0.0;
        }
    }

    Value::operator int() const {
        return (int)(intmax_t)*this;
    }

    Value::operator intmax_t() const {
        switch (impl_->type) {
            case Type::Integer: return impl_->data.integer;
            default: return 0;
        }
    }

    Value::operator size_t() const {
        return (size_t)(intmax_t)*this;
    }

    Value::operator bool() const {
        switch (impl_->type) {
            case Type::Boolean: return impl_->data.boolean;
            default: return false;
        }
    }

    auto Value::GetType() const -> Type {
        if (impl_ == nullptr) {
            return Type::Invalid;
        }
        return impl_->type;
    }

    bool Value::operator==(const Value& other) const {
        if (this == &other) {
            return true;
        }
        switch (impl_->type) {
            case Type::Boolean: return impl_->data.boolean == (bool)other;
            case Type::Error: return *impl_->data.error == (const std::string&)other;
            case Type::Integer: return impl_->data.integer == (intmax_t)other;
            case Type::Real: return impl_->data.real == (double)other;
            case Type::Text: return *impl_->data.text == (const std::string&)other;
            case Type::Invalid: return other.impl_->type == Type::Invalid;
            case Type::Null: return other.impl_->type == Type::Null;
            default: return false;
        }
    }

    bool Value::operator!=(const Value& other) const {
        return !(*this == other);
    }

    Value& Value::operator=(const char* text) {
        *this = Value(text);
        return *this;
    }

    Value& Value::operator=(const std::string& text) {
        *this = Value(text);
        return *this;
    }

    Value& Value::operator=(std::string&& text) {
        *this = Value(std::move(text));
        return *this;
    }

    Value& Value::operator=(double real) {
        *this = Value(real);
        return *this;
    }

    Value& Value::operator=(int integer) {
        *this = Value(integer);
        return *this;
    }

    Value& Value::operator=(intmax_t integer) {
        *this = Value(integer);
        return *this;
    }

    Value& Value::operator=(size_t integer) {
        *this = Value(integer);
        return *this;
    }

    Value& Value::operator=(bool boolean) {
        *this = Value(boolean);
        return *this;
    }

    Value& Value::operator=(nullptr_t null) {
        *this = Value(nullptr);
        return *this;
    }

    Value Value::Error(const std::string& error) {
        Value value;
        value.impl_->type = Type::Error;
        value.impl_->data.error = new std::string(error);
        return value;
    }

    void PrintTo(
        const Value& value,
        std::ostream* os
    ) {
        switch (value.GetType()) {
            case Value::Type::Boolean: {
                *os << ((bool)value ? "true" : "false");
            } break;

            case Value::Type::Error: {
                *os << "error(\"" << ((std::string)value) << "\")";
            } break;

            case Value::Type::Integer: {
                *os << ((intmax_t)value);
            } break;

            case Value::Type::Null: {
                *os << "null";
            } break;

            case Value::Type::Real: {
                *os << ((double)value);
            } break;

            case Value::Type::Text: {
                *os << "\"" << ((std::string)value) << "\"";
            } break;

            default: {
                *os << "invalid";
            } break;
        }
    }

}
