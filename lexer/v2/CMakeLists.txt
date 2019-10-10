cmake_minimum_required(VERSION 3.10)

# Boost.Spirit X3 requires c++14
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

add_executable(lexer-v2 main.cpp lexer.cpp)
target_compile_options(lexer-v2 PRIVATE -Wall -Wpedantic)

add_executable(lexer-test-v2 test_main.cpp lexer.cpp)
target_compile_options(lexer-test-v2 PRIVATE -Wall -Wpedantic)
