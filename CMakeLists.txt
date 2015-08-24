cmake_minimum_required(VERSION 2.8)
project(gpulp CXX)

enable_testing(true)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(OpenCV REQUIRED)

ADD_DEFINITIONS(
    -std=c++11
)

include_directories(include)

#####      float point     #####
# libs
# unit tests

#####      fixed point     #####
# libs
# unit tests

#####   functional tests   #####
add_executable(ft_surface_to_image tests/ft_surface_to_image.cpp)
target_link_libraries(ft_surface_to_image ${OpenCV_LIBS})

add_test(AllTests test_runner)

#####       playground     #####
add_executable(test_runner tests/test_runner.cpp)
target_link_libraries(test_runner ${GTEST_LIBRARIES} pthread)


add_executable(playground tests/playground.cpp)
target_link_libraries(playground)

#### tools ####
add_executable(simulator src/simulator.cpp)
