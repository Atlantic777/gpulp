#ifndef GPULP_MEMORYMANAGER_H
#define GPULP_MEMORYMANAGER_H

#include "gpulp/gpulp_utils.h"
#include <map>

namespace gpulp {
class MemoryManager {
    public:
        void addTexture(TextureMono t);
        TextureMono getTexture(int id);
        int getLocation(int id);

    private:
        void initMemory(int size);
        std::map<int, TextureMono> storage;
};
}

#endif
