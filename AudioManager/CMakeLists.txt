cmake_minimum_required(VERSION 3.28)
project(AudioManager)

set(SOURCES
    AudioManager.cpp
)
set(HEADERS
    AudioManager.h
)
add_library(AudioManager ${SOURCES} ${HEADERS})
target_include_directories(AudioManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
