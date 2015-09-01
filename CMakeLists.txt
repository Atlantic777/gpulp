cmake_minimum_required(VERSION 2.8)
project(gpulp CXX)
set(EXECUTABLE_OUTPUT_PATH bin)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_definitions(-std=c++11)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(OpenCV REQUIRED)

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)
