#include "gpulp/CmdGenerator.h"
#include <sstream>
#include <iostream>

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
  std::stringstream res;
  res << "# RESOURCES\n";
  int allocator;

  for(auto i : resources) {
    res << "0x0000 "
        << i.second.path << " "
        << i.second.size.width << " "
        << i.second.size.height << "\n";
  }

  return res.str();
}

std::string CmdGenerator::dumpCommands() {
  std::stringstream res;

  res << "# CMDS\n";

  for(auto i : objects) {
    res << i.location.x << " " << i.location.y << " "
        << "0x0000 "
        << i.texture.size.width << " " << i.texture.size.height << " "
        << i.size.width << " " << i.size.height << " "
        << i.culling << " " << (int)(i.alpha*255) << "\n";
  }

  return res.str();
}

void CmdGenerator::collectResources() {
  for(auto obj : scene->objects) {
    resources[obj.texture.path] = obj.texture;
  }
}

void CmdGenerator::collectObjects() {
  // TODO: this is actually a tree
  for(auto obj : scene->objects) {
    objects.push_back(obj);
  }
}

void CmdGenerator::setScene(Scene *s) {
  if(s == NULL)
    return;

  scene = s;

  collectResources();
  collectObjects();
}
