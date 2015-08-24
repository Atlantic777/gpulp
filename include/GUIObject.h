#ifndef GPULP_GUIOBJECT_H
#define GPULP_GUIOBJECT_H

#include <list>
#include "gpulp_utils.h"

namespace gpulp {
struct GUIObject {
  Location  location;
  Scale     scale;
  Texture   texture;
  float       alpha;

  std::list<GUIObject*> children;
  GUIObject *parent;
};
}

#endif
