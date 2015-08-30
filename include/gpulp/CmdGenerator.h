#ifndef GPULP_CMDGENERATOR_H
#define GPULP_CMDGENERATOR_H

#include <iostream>
#include <string>
#include "Scene.h"

namespace gpulp {
class CmdGenerator {
  private:
    std::list<GUIObject*> objects;
    std::list<std::string> resources;
    Scene *scene;

    std::string collectResources();
    std::string dumpWorldDescription();
    std::string dumpResources();
    std::string dumpCommands();


  public:
    CmdGenerator() { scene = NULL; }

    void setScene(Scene *s) {
      if(s)
        scene = s;
    }

    std::string generate();
};
}

#endif
