cmake_minimum_required(VERSION 3.28)
project(MediaPlayer)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(HMI)
add_subdirectory(AudioManager)
add_subdirectory(AHAL)

add_executable(player main.cpp)
target_link_libraries(player HMI AudioManager AHAL m asound)