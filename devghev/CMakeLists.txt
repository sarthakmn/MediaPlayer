cmake_minimum_required(VERSION 3.10)
project(devghev_shared_memory)

set(CMAKE_CXX_STANDARD 17)

# Library
add_library(devghev SHARED
    src/devghev.cpp
)
target_include_directories(devghev PUBLIC include)

# Examples
add_executable(writer example/writer.cpp)
target_link_libraries(writer devghev pthread)

add_executable(reader example/reader.cpp)
target_link_libraries(reader devghev pthread)