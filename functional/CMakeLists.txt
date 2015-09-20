add_executable(EmptyScene EmptyScene.cpp)
target_link_libraries(EmptyScene
  ${GPULP_LIBS}
  ${SIMULATOR_LIBS}
  ${OpenCV_LIBS}
  )

add_executable(WhiteStripe WhiteStripe.cpp)
target_link_libraries(WhiteStripe
  ${GPULP_LIBS}
  ${SIMULATOR_LIBS}
  ${OpenCV_LIBS}
  )
