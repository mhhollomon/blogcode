cmake_minimum_required(VERSION 2.6)
project(errors LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

add_executable(v1 v1.cpp)
add_executable(v2 v2.cpp)
add_executable(v3 v3.cpp)
add_executable(v4 v4.cpp)
add_executable(v5 v5.cpp)
