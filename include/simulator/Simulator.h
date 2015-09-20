#ifndef GPULP_SIMULATOR_H
#define GPULP_SIMULATOR_H

#include "gpulp/Scene.h"
#include "simulator/FrameBuffer.h"

namespace gpulp {
class Simulator {
  public:
    void setScene(Scene *s);
    FrameBuffer* render();

  private:
    Scene *scene;
    FrameBuffer *fb;
    void renderOne(GUIObject obj);
};
}

#endif
