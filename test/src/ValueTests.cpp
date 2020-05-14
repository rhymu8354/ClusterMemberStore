/**
 * @file ValueTests.cpp
 *
 * This module contains unit tests of the Database::Value class.
 */

#include <ClusterMemberStore/Value.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

using namespace ClusterMemberStore;

/**
 * This is the test fixture for these tests, providing common
 * setup and teardown for each test.
 */
struct ValueTests
    : public ::testing::Test
{
};

TEST_F(ValueTests, Default_Value) {
    // Arrange

    // Act
    Value value;

    // Assert
    EXPECT_EQ(Value::Type::Invalid, value.GetType());
}

TEST_F(ValueTests, Construct_Text_C_String_Value) {
    // Arrange

    // Act
    Value value("Hello!");

    // Assert
    EXPECT_EQ(Value::Type::Text, value.GetType());
    EXPECT_STREQ("Hello!", (const char*)value);
}

TEST_F(ValueTests, Assign_Text_C_String_Value) {
    // Arrange
    Value value;

    // Act
    value = "Hello!";

    // Assert
    EXPECT_EQ(Value::Type::Text, value.GetType());
    EXPECT_EQ(std::string("Hello!"), (std::string)value);
}

TEST_F(ValueTests, Construct_Text_Copy_Value) {
    // Arrange
    const std::string hello("Hello!");

    // Act
    Value value(hello);

    // Assert
    EXPECT_EQ(Value::Type::Text, value.GetType());
    EXPECT_EQ(hello, (std::string)value);
}

TEST_F(ValueTests, Assign_Text_Copy_Value) {
    // Arrange
    const std::string hello("Hello!");
    Value value;

    // Act
    value = hello;

    // Assert
    EXPECT_EQ(Value::Type::Text, value.GetType());
    EXPECT_EQ(hello, (std::string)value);
}

TEST_F(ValueTests, Construct_Text_Move_Value) {
    // Arrange
    std::string hello("Hello!");

    // Act
    Value value(std::move(hello));

    // Assert
    EXPECT_EQ(Value::Type::Text, value.GetType());
    EXPECT_EQ(std::string("Hello!"), (std::string)value);
}

TEST_F(ValueTests, Assign_Text_Move_Value) {
    // Arrange
    std::string hello("Hello!");
    Value value;

    // Act
    value = std::move(hello);

    // Assert
    EXPECT_EQ(Value::Type::Text, value.GetType());
    EXPECT_EQ(std::string("Hello!"), (std::string)value);
}

TEST_F(ValueTests, Construct_Real_Value) {
    // Arrange
    Value value;

    // Act
    value = 1.23;

    // Assert
    EXPECT_EQ(Value::Type::Real, value.GetType());
    EXPECT_EQ(1.23, (double)value);
}

TEST_F(ValueTests, Assign_Real_Value) {
    // Arrange

    // Act
    Value value(1.23);

    // Assert
    EXPECT_EQ(Value::Type::Real, value.GetType());
    EXPECT_EQ(1.23, (double)value);
}

TEST_F(ValueTests, Construct_Integer_Value) {
    // Arrange

    // Act
    Value value1(42);
    Value value2((intmax_t)12345);
    Value value3((size_t)9001);

    // Assert
    EXPECT_EQ(Value::Type::Integer, value1.GetType());
    EXPECT_EQ(Value::Type::Integer, value2.GetType());
    EXPECT_EQ(Value::Type::Integer, value3.GetType());
    EXPECT_EQ(42, (int)value1);
    EXPECT_EQ((intmax_t)12345, (intmax_t)value2);
    EXPECT_EQ((size_t)9001, (size_t)value3);
}

TEST_F(ValueTests, Assign_Integer_Value) {
    // Arrange
    Value value1;
    Value value2;
    Value value3;

    // Act
    value1 = 42;
    value2 = (intmax_t)12345;
    value3 = (size_t)9001;

    // Assert
    EXPECT_EQ(Value::Type::Integer, value1.GetType());
    EXPECT_EQ(Value::Type::Integer, value2.GetType());
    EXPECT_EQ(Value::Type::Integer, value3.GetType());
    EXPECT_EQ(42, (int)value1);
    EXPECT_EQ((intmax_t)12345, (intmax_t)value2);
    EXPECT_EQ((size_t)9001, (size_t)value3);
}

TEST_F(ValueTests, Construct_Boolean_Value) {
    // Arrange

    // Act
    Value value1(true);
    Value value2(false);

    // Assert
    EXPECT_EQ(Value::Type::Boolean, value1.GetType());
    EXPECT_EQ(Value::Type::Boolean, value2.GetType());
    EXPECT_EQ(true, (bool)value1);
    EXPECT_EQ(false, (bool)value2);
}

TEST_F(ValueTests, Assign_Boolean_Value) {
    // Arrange
    Value value1;
    Value value2;

    // Act
    value1 = true;
    value2 = false;

    // Assert
    EXPECT_EQ(Value::Type::Boolean, value1.GetType());
    EXPECT_EQ(Value::Type::Boolean, value2.GetType());
    EXPECT_EQ(true, (bool)value1);
    EXPECT_EQ(false, (bool)value2);
}

TEST_F(ValueTests, Construct_Null_Value) {
    // Arrange

    // Act
    Value value(nullptr);

    // Assert
    EXPECT_EQ(Value::Type::Null, value.GetType());
}

TEST_F(ValueTests, Assign_Null_Value) {
    // Arrange
    Value value;

    // Act
    value = nullptr;

    // Assert
    EXPECT_EQ(Value::Type::Null, value.GetType());
}

TEST_F(ValueTests, Construct_Error_Value) {
    // Arrange
    const auto message = "REEEEEEEEEEE";

    // Act
    auto value = Value::Error(message);

    // Assert
    EXPECT_EQ(Value::Type::Error, value.GetType());
    EXPECT_STREQ(message, (const char*)value);
}

TEST_F(ValueTests, Copy_Error_Value) {
    // Arrange
    const auto message = "REEEEEEEEEEE";
    const auto value1 = Value::Error(message);

    // Act
    Value value2(value1);

    // Assert
    EXPECT_EQ(Value::Type::Error, value2.GetType());
    EXPECT_STREQ(message, (const char*)value2);
}

TEST_F(ValueTests, Move_Error_Value) {
    // Arrange
    const auto message = "REEEEEEEEEEE";
    auto value1 = Value::Error(message);

    // Act
    Value value2(std::move(value1));

    // Assert
    EXPECT_EQ(Value::Type::Error, value2.GetType());
    EXPECT_STREQ(message, (const char*)value2);
}

TEST_F(ValueTests, Copy_Construct_Value) {
    // Arrange
    Value value1(42);

    // Act
    Value value2(value1);

    // Assert
    EXPECT_EQ(value1, value2);
}

TEST_F(ValueTests, Move_Construct_Value) {
    // Arrange
    Value value1("Hello!");

    // Act
    Value value2(std::move(value1));

    // Assert
    EXPECT_EQ("Hello!", (const std::string &)value2);
}

TEST_F(ValueTests, Copy_Assign_Value) {
    // Arrange
    Value value1(42);
    Value value2;

    // Act
    value2 = value1;

    // Assert
    EXPECT_EQ(value1, value2);
}

TEST_F(ValueTests, Move_Assign_Value) {
    // Arrange
    Value value1("Hello!");
    Value value2;

    // Act
    value2 = std::move(value1);

    // Assert
    EXPECT_EQ("Hello!", (const std::string &)value2);
}

TEST_F(ValueTests, Unspecified_State_After_Move_Construction) {
    // Arrange
    Value value1("Hello!");

    // Act
    Value value2(std::move(value1));

    // Assert
    EXPECT_EQ("Hello!", (const std::string &)value2);
    EXPECT_EQ(Value::Type::Invalid, value1.GetType());
}

TEST_F(ValueTests, Unspecified_State_After_Move_Assignment) {
    // Arrange
    Value value1("Hello!");
    Value value2;

    // Act
    value2 = std::move(value1);

    // Assert
    EXPECT_EQ("Hello!", (const std::string &)value2);
    EXPECT_EQ(Value::Type::Invalid, value1.GetType());
}

TEST_F(ValueTests, PrintTo) {
    // Arrange
    const auto print = [](const Value& value){
        std::ostringstream builder;
        PrintTo(value, &builder);
        return builder.str();
    };

    const std::vector< Value > values{
        true,
        Value::Error("REEEEEEE"),
        42,
        Value(),
        nullptr,
        1.23,
        "Hello!"
    };

    // Act
    std::vector< std::string > prints;
    for (const auto& value: values) {
        prints.push_back(print(value));
    }

    // Assert
    EXPECT_EQ(
        std::vector< std::string >({
            "true",
            "error(\"REEEEEEE\")",
            "42",
            "invalid",
            "null",
            "1.23",
            "\"Hello!\"",
        }),
        prints
    );
}
