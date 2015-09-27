add_library(cmdgenerator CmdGenerator.cpp)
add_library(cmdreader CmdReader.cpp)
add_library(gpulpcommand "Command.cpp")
add_library(utils gpulp_utils.cpp)
add_library(guiobject GUIObject.cpp)
add_library(scene Scene.cpp)
add_library(libgravityutils gravity_utils.cpp)

add_library(libpainter Painter.cpp)
target_link_libraries(libpainter libgravityutils)

add_library(libfixedpoint fixed_point.cpp)

