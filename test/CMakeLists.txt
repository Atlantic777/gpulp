file(GLOB srcs */*.cpp)

set(GPULP_LIBS
  cmdgenerator
)

add_executable(test_runner test_runner.cpp ${srcs})
target_link_libraries(test_runner
    ${GTEST_LIBRARIES}
    ${GPULP_LIBS}
    pthread
)
