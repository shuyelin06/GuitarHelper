# To use:
# cd into the build/ directory, and run "cmake .."
# After the build is done, the executable can be located in build/bin
cmake_minimum_required(VERSION 3.28)
project(GuitarHelper VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(GuitarHelper src/main.cpp src/RecorderWindow.cpp src/Recorder.cpp)
target_compile_features(GuitarHelper PRIVATE cxx_std_17)

target_include_directories(GuitarHelper PRIVATE src)

target_link_libraries(GuitarHelper PRIVATE SFML::Graphics)
target_link_libraries(GuitarHelper PRIVATE SFML::Audio)