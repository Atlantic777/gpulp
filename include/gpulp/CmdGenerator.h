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
    std::string dumpSceneDescription();
    std::string dumpResources();
    std::string dumpCommands();

  public:
    CmdGenerator() {
      scene = NULL;
    }

    void setScene(Scene *s) {
      if(s)
        scene = s;
    }
    std::string generate() {
      if(scene) {
        // dump scene description
        // dump resources
        // dump commands
        return "some scene!";
      }
      else {
        std::cout << "Scene not set!" << std::endl;
        return "";
      }
    }
};
}

#endif
