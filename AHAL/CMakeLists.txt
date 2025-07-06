set(SOURCES
    src/ahal.cpp
)

set(HEADERS
    include/ahal.h
)

add_library(AHALlib STATIC ${SOURCES} ${HEADERS})
target_include_directories(AHALlib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    /usr/local/include/
)

# Now only main.cpp goes into pfAHAL
add_executable(pfAHAL main.cpp)

target_include_directories(pfAHAL PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    /usr/local/include
)

target_link_libraries(pfAHAL
    AHALlib
    devghev
    audio
    m
    pthread
    asound
)

# Install to /usr/bin
install(TARGETS pfAHAL RUNTIME DESTINATION /usr/bin)
