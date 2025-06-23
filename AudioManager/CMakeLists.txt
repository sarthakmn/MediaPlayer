cmake_minimum_required(VERSION 3.22.1)
project(AudioManager)

set(SOURCES
    decoder.cpp
    AudioManager.cpp
)
set(HEADERS
    decoder.h
    AudioManager.h
)
add_library(AudioManager ${SOURCES} ${HEADERS})
target_include_directories(AudioManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
