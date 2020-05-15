# CMakeLists.txt for DatabaseAbstractions

cmake_minimum_required(VERSION 3.8)
set(This DatabaseAbstractions)

set(Headers
    include/DatabaseAbstractions/Database.hpp
    include/DatabaseAbstractions/Value.hpp
)

set(Sources
    src/Value.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

target_include_directories(${This} PUBLIC include)

add_subdirectory(test)
