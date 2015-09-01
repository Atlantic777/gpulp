#ifndef GPULP_SIMULATOR_H
#define GPULP_SIMULATOR_H

#include "gpulp/Scene.h"
#include "opencv2/opencv.hpp"

namespace gpulp {
class Simulator {
  public:
    void setScene(Scene *s) { scene = s; }
    cv::Mat render();

  private:
    Scene *scene;
};
}

#endif
