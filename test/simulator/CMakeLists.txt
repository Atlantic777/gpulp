file(GLOB srcs *.cpp)

add_executable(testsimulator ${srcs})

target_link_libraries(testsimulator
    ${GTEST_LIBRARIES}
    pthread
)
