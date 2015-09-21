#include "gtest/gtest.h"
#include "gpulp/Painter.h"
#include "gpulp/gpulp_utils.h"
#include "simulator/FrameBuffer.h"
#include "gpulp/GUIObject.h"

using namespace gpulp;

TEST(PainterBilinearFloat, Blit) {
  PainterBilinearFloat p;
  FrameBufferMono fb(Size(100, 100));
  
  TextureMono t = TextureMono::fromColor("white", Size(10, 10));
  GUIObject obj;
  obj.location = Location(0, 0);
  obj.scale = Scale(1, 1);
  obj.texture = t;

  p.render(fb, obj);
}
