cmake_minimum_required(VERSION 3.5)
project(MediaPlayerControls)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)   # <-- THIS LINE FIXES THE VTABLE ISSUE

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(MediaPlayerControls
    main.cpp
    mediacontrols.cpp
    mediacontrols.h
)
target_include_directories(MediaPlayerControls PRIVATE target_include_directories(MediaPlayerControls PRIVATE /usr/local/include/))
target_link_libraries(MediaPlayerControls PRIVATE Qt5::Widgets /usr/local/lib/libdevghev.so pthread)
