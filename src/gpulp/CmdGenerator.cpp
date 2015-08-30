#include "gpulp/CmdGenerator.h"
#include <sstream>

using namespace gpulp;

std::string CmdGenerator::generate() {
  if(scene == NULL)
    return "Scene not set!";

  std::stringstream res;

  res << dumpWorldDescription();
  res << dumpResources();
  res << dumpCommands();

  return res.str();
}

std::string CmdGenerator::dumpWorldDescription() {
  std::stringstream res;

  res << "# WORLD" << std::endl;

  res << scene->size.width << " "
      << scene->size.height << " "
      << (int)scene->channels << std::endl;

  return res.str();
}

std::string CmdGenerator::dumpResources() {
  return "# RESOURCES\n";
}

std::string CmdGenerator::dumpCommands() {
  return "# CMDS\n";
}
