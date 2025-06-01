cmake_minimum_required(VERSION 3.28)

SET(SRC_FILES
    Figure.cpp
    BoxPlot.cpp
    Text.cpp)

add_library(display STATIC ${SRC_FILES})
target_include_directories(display PUBLIC ${SFML_INCLUDE_DIR})