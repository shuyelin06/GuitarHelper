# To use:
# cd into the build/ directory, and run "cmake .."
# After the build is done, the executable can be located in build/bin
cmake_minimum_required(VERSION 3.28)
project(GuitarHelper VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)

# Fetch SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_GetProperties(SFML)
FetchContent_MakeAvailable(SFML)

set(SFML_INCLUDE_DIR "${SFML_SOURCE_DIR}/include")

SET(SRC_FILES
    src/main.cpp 
    src/Recorder.cpp 
    src/Fourier.cpp)

# Add each of my directories
add_subdirectory(src/display)

add_executable(GuitarHelper ${SRC_FILES})
target_include_directories(GuitarHelper PRIVATE src)
target_link_libraries(GuitarHelper PRIVATE SFML::Graphics SFML::Audio display)