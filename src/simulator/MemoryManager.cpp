#include "simulator/MemoryManager.h"

using namespace gpulp;

void MemoryManager::addTexture(Texture t) {
  storage[t.id] = t;
}

int MemoryManager::getLocation(int id) {
  return 0;
}

Texture MemoryManager::getTexture(int id) {
  return storage[id];
}
