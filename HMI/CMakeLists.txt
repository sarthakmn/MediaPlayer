cmake_minimum_required(VERSION 3.5)
project(HMI)

set(SOURCE
    hmi.cpp
)
set(HEADER 
    hmi.h
)

add_library(HMI ${SOURCE} ${HEADER})
target_include_directories(HMI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})