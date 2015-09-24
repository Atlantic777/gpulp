#include "gtest/gtest.h"
#include "gpulp/Painter.h"
#include "gpulp/gpulp_utils.h"
#include "simulator/FrameBuffer.h"
#include "gpulp/GUIObject.h"
#include "gpulp/InterpolationContext.h"
#include <iostream>

using namespace gpulp;
using namespace std;

TEST(PainterBilinearFloat, Blit) {
  FrameBufferMono fb(Size(100, 100));

  TextureMono t = TextureMono::fromColor("white", Size(10, 10));
  GUIObject obj;
  obj.location = Location(0, 90);
  obj.size = t.size;
  obj.texture = t;

  PainterBilinearFloat p;

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

TEST(PainterBilinearFloat, GetInterpolationContext) {
  FrameBufferMono fb = FrameBufferMono(Size(10, 10));
  TextureMono t = TextureMono::fromColor("white", Size(2, 2));
  GUIObject obj;
  obj.location = Location(0, 0);
  obj.size = Size(4, 4);
  obj.texture = t;

  PainterBilinearFloat pbf;

  InterpolationContext ctx;
  ctx = pbf.getInterpolationContext(Location(0, 0), fb, obj);

  ASSERT_FALSE(ctx.a == NULL);
  ASSERT_FALSE(ctx.b == NULL);
  ASSERT_FALSE(ctx.c == NULL);
  ASSERT_FALSE(ctx.d == NULL);

  ASSERT_EQ(255, ctx.a->getData()[0]);
  ASSERT_EQ(255, ctx.b->getData()[0]);
  ASSERT_EQ(255, ctx.c->getData()[0]);
  ASSERT_EQ(255, ctx.d->getData()[0]);

  ctx = pbf.getInterpolationContext(Location(2, 0), fb, obj);

  FAIL() << "finish test";
}

TEST(PainterBilinearFloat, StretchBlit) {
  FrameBufferMono fb(Size(10, 10));

  TextureMono t = TextureMono::fromColor("white", Size(2, 2));
  GUIObject obj;
  obj.location = Location(0, 0);
  obj.size = Size(4, 4);
  obj.texture = t;

  PainterBilinearFloat p;

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
