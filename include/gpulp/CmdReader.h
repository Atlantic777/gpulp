#ifndef GPULP_CMDREADER_H
#define GPULP_CMDREADER_H

#include "gpulp/Scene.h"
#include <string>

namespace gpulp{
class CmdReader {
  public:
    CmdReader(std::string in) : input(in) {}
    Scene read();

  private:
    std::string input;

    void readWorld();
    void readResources();
    void readCommands();
    std::string getSection(std::string section);

    // D stands for delimiter
    static const std::string D_WORLD;
    static const std::string D_RESOURCES;
    static const std::string D_CMDS;

    Scene scene;
};
}

#endif
