set(COMMON_LIBS
  ${GPULP_LIBS}
  ${SIMULATOR_LIBS}
  ${OpenCV_LIBS}
  )

add_executable(EmptyScene EmptyScene.cpp)
target_link_libraries(EmptyScene ${COMMON_LIBS})

add_executable(WhiteStripe WhiteStripe.cpp)
target_link_libraries(WhiteStripe ${COMMON_LIBS})

add_executable(LoadTextureFromFile LoadTextureFromFile.cpp)
target_link_libraries(LoadTextureFromFile ${COMMON_LIBS})

add_executable(BilinearFloatInterpolation BilinearFloatInterpolation.cpp)
target_link_libraries(BilinearFloatInterpolation ${COMMON_LIBS})

