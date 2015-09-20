add_library(framebuffer FrameBuffer.cpp)
add_library(memorymanager MemoryManager.cpp)

add_library(libsimulator Simulator.cpp)
target_link_libraries(libsimulator ${OpenCV_LIBS})

add_library(libmemorymanager MemoryManager.cpp)

add_executable(simulator simulator.cpp)
