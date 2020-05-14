# CMakeLists.txt for ClusterMemberStoreTests

cmake_minimum_required(VERSION 3.8)
set(This ClusterMemberStoreTests)

set(Sources
    src/ValueTests.cpp
)

add_executable(${This} ${Sources})
set_target_properties(${This} PROPERTIES
    FOLDER Tests
)

target_link_libraries(${This} PUBLIC
    gtest_main
    ClusterMemberStore
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
