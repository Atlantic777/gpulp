#include "cv_utils/cv_utils.h"
#include "gpulp/GUIObject.h"
#include "gpulp/gpulp_utils.h"
#include "simulator/Simulator.h"

using namespace std;

int main() {
  TextureMono t = LoadTexture("/home/nikola/code/gpulp/res/compiling.png");

  GUIObject obj;
  obj.location = Location(0, 0);
  obj.size = Size(640, 480);
  obj.texture = t;
  obj.parent = NULL;

  Scene scene(obj.size, ch_mono);
  scene.addObject(obj);

  Simulator sim("gravity", "float");
  sim.setScene(&scene);

  FrameBuffer *fb = sim.render();
  cv::Mat m = FrameBuffer2Mat(fb);

  cv::imshow("compiling interpolated", m);

  while(cv::waitKey(0) != 27);

  return 0;
}
