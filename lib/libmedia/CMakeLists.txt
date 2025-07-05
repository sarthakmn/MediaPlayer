cmake_minimum_required(VERSION 3.10)
project(libmedia_shared_memory)

set(CMAKE_CXX_STANDARD 17)

# === Find FFmpeg dependencies ===
find_package(PkgConfig REQUIRED)

pkg_check_modules(AVFORMAT REQUIRED libavformat)
pkg_check_modules(AVCODEC REQUIRED libavcodec)
pkg_check_modules(AVUTIL REQUIRED libavutil)
pkg_check_modules(SWRESAMPLE REQUIRED libswresample)

# === Shared Library ===
add_library(media SHARED
    src/decoder.cpp
)

# === Include Directories ===
target_include_directories(media PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${AVFORMAT_INCLUDE_DIRS}
    ${AVCODEC_INCLUDE_DIRS}
    ${AVUTIL_INCLUDE_DIRS}
    ${SWRESAMPLE_INCLUDE_DIRS}
)

# === Link FFmpeg Libraries ===
target_link_libraries(media
    ${AVFORMAT_LIBRARIES}
    ${AVCODEC_LIBRARIES}
    ${AVUTIL_LIBRARIES}
    ${SWRESAMPLE_LIBRARIES}
)

# === Install Rules ===
install(TARGETS media
        LIBRARY DESTINATION lib)

install(DIRECTORY include/
        DESTINATION include)
