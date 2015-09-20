#include "cv_utils/cv_utils.h"
#include "gpulp/GUIObject.h"
#include "gpulp/gpulp_utils.h"
#include "simulator/Simulator.h"

using namespace gpulp;

int main() {
  TextureMono t = LoadTexture("/home/nikola/code/gpulp/res/compiling.png");

  GUIObject obj;
  obj.location = Location(0, 0);
  obj.scale    = Scale(1, 1);
  obj.texture  = t;
  obj.parent   = NULL;

  Scene scene(t.size, ch_mono);
  scene.addObject(obj);

  Simulator sim;
  sim.setScene(&scene);

  FrameBuffer *fb = sim.render();
  cv::Mat m = FrameBuffer2Mat(fb);

  cv::imshow("compiling", m);

  while(cv::waitKey(0) != 27);

  return 0;
}
