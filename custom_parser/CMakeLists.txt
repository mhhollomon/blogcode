cmake_minimum_required(VERSION 3.12)
project (CustomParser)

include_directories(BEFORE ${BOOSTPATH}/include)

add_executable(custom_parser custom_parser.cpp)
