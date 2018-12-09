cmake_minimum_required(VERSION 3.12)
project (BlogCode)

set (BOOSTPATH ${HOME}/local)

link_directories(${BOOSTPATH}/lib)

add_subdirectory(parse_ident)

add_subdirectory(custom_parser)
add_subdirectory(errors)
