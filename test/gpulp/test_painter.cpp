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
  obj.scale = Scale(1, 1);
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
  obj.scale = Scale(2, 2);
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
}

void check_locations_22(std::map<char, Location> m) {
  Location a = m['a'];
  Location b = m['b'];
  Location c = m['c'];
  Location d = m['d'];

  ASSERT_EQ(0, a.x);
  ASSERT_EQ(0, a.y);

  ASSERT_EQ(1, b.x);
  ASSERT_EQ(0, b.y);

  ASSERT_EQ(0, c.x);
  ASSERT_EQ(1, c.y);

  ASSERT_EQ(1, d.x);
  ASSERT_EQ(1, d.y);
}

TEST(PainterBilinearFloat, GetInterpolationLocations22) {
  FrameBufferMono fb = FrameBufferMono(Size(10, 10));
  TextureMono t = TextureMono::fromColor("white", Size(2, 2));
  GUIObject obj;
  obj.location = Location(0, 0);
  obj.scale = Scale(2, 2);
  obj.texture = t;

  PainterBilinearFloat pbf;
  std::map<char, Location> m;

  for(int col = 0; col < 4; col++) {
    for(int row = 0; row < 4; row++) {
      check_locations_22(pbf.getSourceLocations(Location(row, col), obj));
    }
  }
}

void check_locations_11(std::map<char, Location> m) {
  Location a = m['a'];
  Location b = m['b'];
  Location c = m['c'];
  Location d = m['d'];

  ASSERT_EQ(0, a.x);
  ASSERT_EQ(0, a.y);

  ASSERT_EQ(0, b.x);
  ASSERT_EQ(0, b.y);

  ASSERT_EQ(0, c.x);
  ASSERT_EQ(0, c.y);

  ASSERT_EQ(0, d.x);
  ASSERT_EQ(0, d.y);
}

TEST(PainterBilinearFloat, GetInterpolationLocations11) {
  FrameBufferMono fb = FrameBufferMono(Size(10, 10));
  TextureMono t = TextureMono::fromColor("white", Size(1, 1));
  GUIObject obj;
  obj.location = Location(0, 0);
  obj.scale = Scale(2, 2);
  obj.texture = t;

  PainterBilinearFloat pbf;
  std::map<char, Location> m;

  for(int col = 0; col < 4; col++) {
    for(int row = 0; row < 4; row++) {
      check_locations_11(pbf.getSourceLocations(Location(row, col), obj));
    }
  }
}

TEST(PainterBilinearFloat, StretchBlit) {
  FrameBufferMono fb(Size(10, 10));

  TextureMono t = TextureMono::fromColor("white", Size(2, 2));
  GUIObject obj;
  obj.location = Location(0, 0);
  obj.scale = Scale(2, 2);
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
