cmake_minimum_required(VERSION 3.10)

project(swcpt)
add_executable(swcpt main.cpp
    leetcode/3904.cpp)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)