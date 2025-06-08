cmake_minimum_required(VERSION 3.5)
project(AHAL)
set(HEADER
    wav_parser.h
    ahal.h
)
set(SOURCE
    wav_parser.cpp
    ahal.cpp
)
add_library(AHAL ${HEADER} ${SOURCE})
target_include_directories(AHAL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
