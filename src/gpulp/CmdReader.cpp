#include "gpulp/CmdReader.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace gpulp;

const std::string CmdReader::D_WORLD     = std::string("# WORLD");
const std::string CmdReader::D_RESOURCES = std::string("# RESOURCES");
const std::string CmdReader::D_CMDS      = std::string("# CMDS");

Scene CmdReader::read() {
  readWorld();
  readResources();
  readCommands();

  return scene;
}

void CmdReader::readWorld() {
  int start = input.find(D_WORLD) + D_WORLD.length() + 1;
  int stop  = input.find(D_RESOURCES);
  int len   = stop - start - 1;

  std::stringstream world;
  world << input.substr(start, len);

  int width, height, chans;
  world >> width >> height >> chans;

  scene.size.width  = width;
  scene.size.height = height;
  scene.channels = Channels(chans);
}

void CmdReader::readResources() {
}

void CmdReader::readCommands() {
}
