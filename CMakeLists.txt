# CMakeLists.txt for ClusterMemberStore

cmake_minimum_required(VERSION 3.8)
set(This ClusterMemberStore)

set(Headers
    include/ClusterMemberStore/Database.hpp
)

set(Sources
    src/Database.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

target_include_directories(${This} PUBLIC include)
