cmake_minimum_required(VERSION 3.22.1)
project(AHAL)

set(SOURCE
#    src/wav_parser.cpp
    src/ahal.cpp
)
add_library(AHAL ${HEADER} ${SOURCE})
target_include_directories(AHAL PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
target_include_directories(AHAL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
