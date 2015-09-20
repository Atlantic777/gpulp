#include "simulator/Simulator.h"
#include "gpulp/gpulp_utils.h"
#include "opencv2/opencv.hpp"
#include "cv_utils/cv_utils.h"

using namespace gpulp;

int main() {
  Scene scene(Size(100, 100), ch_mono);

  Simulator sim;
  sim.setScene(&scene);

  FrameBuffer *fb = sim.render();
  cv::Mat m = FrameBuffer2Mat(fb);

  cv::imshow("EmptyScene", m);

  while(cv::waitKey(0) != 27);

  return 0;
}
