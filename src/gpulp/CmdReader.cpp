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
  std::stringstream world;
  world << getSection(D_WORLD);

  int width, height, chans;
  world >> width >> height >> chans;

  scene.size.width  = width;
  scene.size.height = height;
  scene.channels = Channels(chans);
}

void CmdReader::readResources() {
  std::stringstream resources;
  resources << getSection(D_RESOURCES);

  int location, width, height;
  std::string name;

  resources >> std::hex >> location >> name >> width >> height;

  scene.resources[name] = TextureMono(name, Size(width, height));
  scene.resources[name].location = location;
}

void CmdReader::readCommands() {
}

std::string CmdReader::getSection(std::string section) {
  int start = input.find(section) + section.length() + 1;
  int stop  = input.find("#");
  int len   = stop - start - 1;

  return input.substr(start, len);
}
