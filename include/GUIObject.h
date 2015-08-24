#ifndef GPULP_GUIOBJECT_H
#define GPULP_GUIOBJECT_H

#include <list>
#include "gpulp_utils.h"

namespace gpulp {
class GUIObject {
    public:

    private:
        Location  location;
        Scale     scale;
        Texture   texture;
        int       alpha;

        std::list<GUIObject*> children;
        GUIObject *parent;
};
}

#endif
