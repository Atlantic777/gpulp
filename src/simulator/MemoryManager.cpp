#include "simulator/MemoryManager.h"

using namespace gpulp;

void MemoryManager::addTexture(TextureMono t) {
  storage[t.id] = t;
}

int MemoryManager::getLocation(int id) {
  return 0;
}

TextureMono MemoryManager::getTexture(int id) {
  return storage[id];
}
