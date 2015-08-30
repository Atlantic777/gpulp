cmake_minimum_required(VERSION 2.8)
project(gpulp CXX)
set(EXECUTABLE_OUTPUT_PATH bin)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)
