cmake_minimum_required(VERSION 3.22.1)
project(MediaPlayer)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

# === Add submodules ===
add_subdirectory(lib/devghev)
add_subdirectory(lib/libmedia)
add_subdirectory(lib/libaudio)
add_subdirectory(AudioManager)
add_subdirectory(AHAL)
add_subdirectory(HMI)

# === Main Executable ===
add_executable(pfMediaPlayer main.cpp)

target_include_directories(pfMediaPlayer PRIVATE /usr/local/include)

target_link_libraries(pfMediaPlayer
    devghev
    media
    audio

    m
    pthread
    asound
    avformat
    avcodec
    avutil
    swresample
)
