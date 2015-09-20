#ifndef GPULP_MEMORYMANAGER_H
#define GPULP_MEMORYMANAGER_H

#include "gpulp/gpulp_utils.h"
#include <map>

namespace gpulp {
class MemoryManager {
    public:
        void addTexture(Texture t);
        Texture getTexture(int id);
        int getLocation(int id);

    private:
        void initMemory(int size);
        std::map<int, Texture> storage;
};
}

#endif
