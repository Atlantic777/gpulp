add_library(libmemorymanager MemoryManager.cpp)
add_library(libframebuffer FrameBuffer.cpp)

add_library(libsimulator Simulator.cpp)
target_link_libraries(libsimulator)

add_executable(simulator simulator.cpp)
