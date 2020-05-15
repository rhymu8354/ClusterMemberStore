# CMakeLists.txt for DatabaseAbstractionsTests

cmake_minimum_required(VERSION 3.8)
set(This DatabaseAbstractionsTests)

set(Sources
    src/ValueTests.cpp
)

add_executable(${This} ${Sources})
set_target_properties(${This} PROPERTIES
    FOLDER Tests
)

target_link_libraries(${This} PUBLIC
    gtest_main
    DatabaseAbstractions
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
