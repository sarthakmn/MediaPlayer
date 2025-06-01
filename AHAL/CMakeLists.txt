cmake_minimum_required(VERSION 3.5)
project(AHAL)
set(HEADER
    ahal.h
)
set(SOURCE
    ahal.cpp
)
add_library(AHAL ${HEADER} ${SOURCE})
target_include_directories(AHAL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
