#ifndef GPULP_SIMULATOR_H
#define GPULP_SIMULATOR_H

#include "gpulp/Scene.h"
#include "gpulp/Painter.h"
#include "simulator/FrameBuffer.h"
#include <string>

namespace gpulp {
class Simulator {
  public:
    Simulator(std::string algorithm = "bilinear", std::string mathlib = "float");
    void setScene(Scene *s);
    FrameBuffer* render();

  private:
    Scene *scene;
    FrameBuffer *fb;
    void renderOne(const GUIObject &obj);
    Painter *p;
    std::string algorithm;
    std::string mathlib;
};
}

#endif
