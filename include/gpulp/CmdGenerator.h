#ifndef GPULP_CMDGENERATOR_H
#define GPULP_CMDGENERATOR_H

#include <iostream>
#include <string>
#include "Scene.h"
#include <map>

namespace gpulp {
class CmdGenerator {
  private:
    std::list<GUIObject> objects;
    std::map<std::string, TextureMono> resources;
    Scene *scene;

    void collectResources();
    void collectObjects();
    std::string dumpWorldDescription();
    std::string dumpResources();
    std::string dumpCommands();


  public:
    CmdGenerator() { scene = NULL; }

    void setScene(Scene *s);
    std::string generate();
    std::map<std::string, TextureMono> getResources() { return resources; }
};
}

#endif
