file(GLOB srcs */*.cpp)

# set(GPULP_LIBS
#   cmdgenerator
#   cmdreader
#   utils
# )
#
# set(SIMULATOR_LIBS
#   libsimulator
#   libmemorymanager
# )

add_executable(test_runner test_runner.cpp ${srcs})
target_link_libraries(test_runner
    ${GTEST_LIBRARIES}
    ${GPULP_LIBS}
    ${SIMULATOR_LIBS}
    pthread
)
