cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(SnowflakeGeneration)
set(CMAKE_CXX_STANDARD 11)

set(SRC_FILES
    main.cpp
    lattice.cpp
)

add_subdirectory(rapidjson)

include_directories(rapidjson/include/)

add_executable(snowflake ${SRC_FILES})
