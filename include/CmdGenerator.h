#ifndef GPULP_CMDGENERATOR_H
#define GPULP_CMDGENERATOR_H

namespace gpulp {
class CmdGenerator {
    private:
        std::list<GUIObject*> objects;
        std::list<string> resources;

        bool collectResources();
        bool dumpResources();
        bool dumpCommands();
};
}

#endif
