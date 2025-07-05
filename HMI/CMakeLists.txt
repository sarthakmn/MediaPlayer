cmake_minimum_required(VERSION 3.5)
project(HMI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

# UI Executable only — no duplicate library
add_executable(pfHMI
    main.cpp
    src/mediacontrols.cpp
    include/mediacontrols.h
)

target_include_directories(pfHMI PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    /usr/local/include
)

target_link_libraries(pfHMI
    PRIVATE
    Qt5::Widgets
    devghev
    pthread
)

# Install to /usr/bin
install(TARGETS pfHMI RUNTIME DESTINATION /usr/bin)
