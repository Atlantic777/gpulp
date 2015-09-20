#include "opencv2/opencv.hpp"
#include "cv_utils/cv_utils.h"
#include "simulator/Simulator.h"

using namespace gpulp;

int main() {
  TextureMono t = TextureMono::fromColor("white", Size(100, 50));

  GUIObject obj;
  obj.texture = t;
  obj.location = Location(0, 0);

  Scene scene(Size(100, 100), ch_mono);
  scene.addObject(obj);

  Simulator sim;
  sim.setScene(&scene);

  FrameBuffer *fb = sim.render();
  cv::Mat m = FrameBuffer2Mat(fb);

  cv::imshow("WhiteStripe", m);

  while(cv::waitKey(0) != 27);

  return 0;
}
