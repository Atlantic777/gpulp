#ifndef GPULP_SCENE_H
#define GPULP_SCENE_H

#include <list>
#include "gpulp_utils.h"
#include "GUIObject.h"

namespace gpulp {
struct Scene {
  Size size;
  Channels channels;
  // TODO: Scene is a tree
  std::list<GUIObject> objects;

  Scene(Size s, Channels c) : size(s), channels(c) {}

  void addObject(const GUIObject &obj) {
    objects.push_back(obj);
  }

};
}

#endif
