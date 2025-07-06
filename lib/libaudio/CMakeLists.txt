cmake_minimum_required(VERSION 3.10)
project(libaudio LANGUAGES CXX)

# Create the shared library
add_library(audio SHARED
    src/audio_client.cpp
    src/audio_server.cpp
)

# Include headers for public API
target_include_directories(audio
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Set the output name of the shared library to libaudio.so
set_target_properties(audio PROPERTIES OUTPUT_NAME "audio")

# Optional: Use C++11 or newer
target_compile_features(audio PRIVATE cxx_std_11)

# Optional install rules
install(TARGETS audio
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(FILES include/audio.h DESTINATION include)
