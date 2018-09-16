cmake_minimum_required(VERSION 3.12)
project (ParseIdent)

add_executable(parse_ident_v1 parse_ident_v1.cpp)
target_include_directories(parse_ident_v1 BEFORE PUBLIC ${BOOSTPATH}/include)

add_executable(parse_ident_v2 parse_ident_v2.cpp)
target_include_directories(parse_ident_v2 BEFORE PUBLIC ${BOOSTPATH}/include)

add_executable(parse_ident_v3 parse_ident_v3.cpp)
target_include_directories(parse_ident_v3 BEFORE PUBLIC ${BOOSTPATH}/include)

add_executable(parse_ident_v4 parse_ident_v4.cpp)
target_include_directories(parse_ident_v4 BEFORE PUBLIC ${BOOSTPATH}/include)
