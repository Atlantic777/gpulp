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
  obj.location = Location(0, 90);
  obj.scale = Scale(1, 1);
  obj.texture = t;

  p.render(fb, obj);

  for(int row = 0; row < 100; row++) {
    for(int col = 0; col < 100; col++) {
      if(row >= 90 && col < 10) {
        ASSERT_EQ(255, fb.read(col, row).getData()[0]);
      }
      else {
        ASSERT_EQ(0, fb.read(col, row).getData()[0]);
      }
    }
  }
}

TEST(PainterBilinearFloat, StretchBlit) {
  PainterBilinearFloat p;
  FrameBufferMono fb(Size(10, 10));

  TextureMono t = TextureMono::fromColor("white", Size(2, 2));
  GUIObject obj;
  obj.location = Location(0, 0);
  obj.scale = Scale(2, 2);
  obj.texture = t;

  p.render(fb, obj);

  for(int row = 0; row < 10; row++) {
    for(int col = 0; col < 10; col++) {
      if(row < 2 && col < 2) {
        ASSERT_EQ(255, fb.read(col, row).getData()[0]);
      }
      else {
        ASSERT_EQ(0, fb.read(col, row).getData()[0]);
      }
    }
  }
}
