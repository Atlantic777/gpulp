#include "gtest/gtest.h"
#include "gpulp/Painter.h"
#include "gpulp/gpulp_utils.h"
#include "simulator/FrameBuffer.h"
#include "gpulp/GUIObject.h"
#include "gpulp/InterpolationContext.h"
#include <iostream>

using namespace gpulp;
using namespace std;

void test_blit(FrameBufferMono &fb) {
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

void test_interpolation_context_1(InterpolationContext &ctx) {
  ASSERT_FALSE(ctx.a == NULL);
  ASSERT_FALSE(ctx.b == NULL);
  ASSERT_FALSE(ctx.c == NULL);
  ASSERT_FALSE(ctx.d == NULL);

  ASSERT_EQ(255, ctx.a->getData()[0]);
  ASSERT_EQ(255, ctx.b->getData()[0]);
  ASSERT_EQ(255, ctx.c->getData()[0]);
  ASSERT_EQ(255, ctx.d->getData()[0]);
}

void test_interpolation_context_2(InterpolationContext &ctx) {
  ASSERT_EQ(255, ctx.a->getData()[0]);
  ASSERT_EQ(255, ctx.b->getData()[0]);
  ASSERT_EQ(255, ctx.c->getData()[0]);
  ASSERT_EQ(255, ctx.d->getData()[0]);
}

void test_stretch_blit(FrameBufferMono &fb) {
  for(int row = 0; row < 10; row++) {
    for(int col = 0; col < 10; col++) {
      if(row < 4 && col < 4) {
        ASSERT_EQ(255, fb.read(col, row).getData()[0]);
      }
      else {
        ASSERT_EQ(0, fb.read(col, row).getData()[0]);
      }
    }
  }
}

GUIObject get_object(Size t_size, Size o_size, Location l = Location(0, 0)) {
  TextureMono t = TextureMono::fromColor("white", t_size);
  GUIObject obj;
  obj.location = l;
  obj.size = o_size;
  obj.texture = t;

  return obj;
}


TEST(PainterBilinearFloat, Blit) {
  FrameBufferMono fb(Size(100, 100));
  GUIObject obj = get_object(Size(10, 10), Size(10, 10), Location(0, 90));

  PainterBilinearFloat p;
  p.render(fb, obj);

  test_blit(fb);
}

TEST(PainterBilinearFloat, GetInterpolationContext) {
  FrameBufferMono fb = FrameBufferMono(Size(10, 10));
  GUIObject obj = get_object(Size(2, 2), Size(4, 4));
  PainterBilinearFloat pbf;
  InterpolationContext ctx;

  ctx = pbf.getInterpolationContext(Location(0, 0), fb, obj);
  test_interpolation_context_1(ctx);

  ctx = pbf.getInterpolationContext(Location(2, 0), fb, obj);
  test_interpolation_context_2(ctx);
}

TEST(PainterBilinearFloat, StretchBlit) {
  FrameBufferMono fb(Size(10, 10));
  GUIObject obj = get_object(Size(2, 2), Size(4, 4));

  PainterBilinearFloat p;
  p.render(fb, obj);

  test_stretch_blit(fb);
}
