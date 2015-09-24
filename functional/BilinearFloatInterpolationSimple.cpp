#include "gpulp/GUIObject.h"
#include "gpulp/gpulp_utils.h"
#include "simulator/Simulator.h"
#include "cv_utils/cv_utils.h"

using namespace gpulp;

int main() {
  TextureMono t = TextureMono::fromColor("white", Size(2, 2));

  GUIObject obj;
  obj.location = Location(0, 0);
  obj.size = Size(100, 100);
  obj.texture = t;
  obj.parent = NULL;

  Scene scene(Size(640, 480), ch_mono);
  scene.addObject(obj);

  Simulator sim;
  sim.setScene(&scene);

  FrameBuffer *fb = sim.render();
  cv::Mat m = FrameBuffer2Mat(fb);

  cv::imshow("interpolation simple", m);

  while(cv::waitKey(0) != 27);

  return 0;
}
