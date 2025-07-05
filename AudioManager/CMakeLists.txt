cmake_minimum_required(VERSION 3.22.1)

project(AudioManager)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/AudioManager.cpp
    main.cpp
)

set(HEADERS
    include/AudioManager.h
    include/StateMachine.h
)

# Rename the library to avoid conflict
add_library(AudioManagerLib STATIC ${SOURCES} ${HEADERS})
target_include_directories(AudioManagerLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    /usr/local/include/
)

add_executable(pfAudioManager ${SOURCES} ${HEADERS})
target_include_directories(pfAudioManager PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/AHAL/include
    ${CMAKE_SOURCE_DIR}/lib/devghev/include
    ${CMAKE_SOURCE_DIR}/lib/libmedia/include
    /usr/local/include/
)

target_link_libraries(pfAudioManager
    AudioManagerLib
    AHAL
    devghev
    media
    m
    pthread
    asound
    avformat
    avcodec
    avutil
    swresample
)

# Install to /usr/bin
install(TARGETS pfAudioManager RUNTIME DESTINATION /usr/bin)
