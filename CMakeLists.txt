cmake_minimum_required(VERSION 3.22.1)
project(MediaPlayer)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(HMI)
add_subdirectory(AudioManager)
add_subdirectory(AHAL)

add_executable(player main.cpp)
target_include_directories(player PRIVATE /usr/local/include/)
target_link_libraries(player HMI AudioManager AHAL 
    m 
    asound 
    avformat
    avcodec
    avutil
    swresample
    pthread
    /usr/local/lib/libdevghev.so
    /usr/local/lib/libmedia.so
)