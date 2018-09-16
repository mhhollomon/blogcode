cmake_minimum_required(VERSION 3.12)
project (ParseIdent)

include_directories(BEFORE ${BOOSTPATH}/include)

add_executable(parse_ident_v1 parse_ident_v1.cpp)

add_executable(parse_ident_v2 parse_ident_v2.cpp)

add_executable(parse_ident_v3 parse_ident_v3.cpp)

add_executable(parse_ident_v4 parse_ident_v4.cpp)
