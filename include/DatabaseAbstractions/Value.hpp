#pragma once

/**
 * @file Value.hpp
 *
 * This file defines the DatabaseAbstractions::Value class, which represents
 * an element of data either sent to or retrieved from a database.
 */

#include <memory>
#include <ostream>
#include <stddef.h>
#include <stdint.h>
#include <string>

namespace DatabaseAbstractions {

    class Value {
        // Types
    public:
        enum class Type {
            Boolean,
            Error,
            Integer,
            Invalid,
            Null,
            Real,
            Text,
        };

        // Lifecycle
    public:
        ~Value() noexcept;
        Value(const Value& other);
        Value(Value&& other) noexcept;
        Value& operator=(const Value& other);
        Value& operator=(Value&& other) noexcept;

        // Construction
    public:
        Value();
        Value(const char* text);
        Value(const std::string& text);
        Value(std::string&& text);
        Value(double real);
        Value(int integer);
        Value(intmax_t integer);
        Value(size_t integer);
        Value(bool boolean);
        Value(nullptr_t null);

        // Methods
    public:
        operator const char*() const;
        operator const std::string&() const;
        operator double() const;
        operator int() const;
        operator intmax_t() const;
        operator size_t() const;
        operator bool() const;
        Type GetType() const;
        bool operator==(const Value& other) const;
        bool operator!=(const Value& other) const;
        Value& operator=(const char* text);
        Value& operator=(const std::string& text);
        Value& operator=(std::string&& text);
        Value& operator=(double real);
        Value& operator=(int integer);
        Value& operator=(intmax_t integer);
        Value& operator=(size_t integer);
        Value& operator=(bool boolean);
        Value& operator=(nullptr_t null);
        static Value Error(const std::string& error);

        // Private Properties
    private:
        /**
         * This is the type of structure that contains the private
         * properties of the instance.  It is defined in the implementation
         * and declared here to ensure that it is scoped inside the class.
         */
        struct Impl;

        /**
         * This contains the private properties of the instance.
         */
        std::unique_ptr< Impl > impl_;
    };

    /**
     * This is a support function for Google Test to print out
     * database values.
     *
     * @param[in] value
     *     This is the value to print.
     *
     * @param[in] os
     *     This points to the stream to which to print the value.
     */
    void PrintTo(
        const Value& value,
        std::ostream* os
    );

}
