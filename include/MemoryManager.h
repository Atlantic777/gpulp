#ifndef GPULP_MEMORYMANAGER_H
#define GPULP_MEMORYMANAGER_H

namespace gpulp {
class MemoryManager {
    public:
        void addTexture(); // location, data and size
        int read(int location);
    private:
        void initMemory(int size);
};
}

#endif
