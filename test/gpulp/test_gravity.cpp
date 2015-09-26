#include "gtest/gtest.h"
#include "gpulp/gravity_utils.h"
#include "gpulp/InterpolationContext.h"

using namespace gpulp;

TEST(GravityFloat, GetGravityDistances) {
  InterpolationContext ctx;
  ctx.dx = 0.2;
  ctx.dy = 0.4;

  std::vector<float> dst = get_gravity_distances(ctx);

  ASSERT_EQ(4, dst.size());

  ASSERT_FLOAT_EQ(0.04 + 0.16, dst[0]); // top left
  ASSERT_FLOAT_EQ(0.64 + 0.16, dst[1]); // top right
  ASSERT_FLOAT_EQ(0.04 + 0.36, dst[2]); // bottom left
  ASSERT_FLOAT_EQ(0.64 + 0.36, dst[3]); // bottom right
}

TEST(GravityFloat, SortPixels) {
  InterpolationContext ctx;
  ctx.a = new PixelMono(40);
  ctx.b = new PixelMono(30);
  ctx.c = new PixelMono(20);
  ctx.d = new PixelMono(10);

  std::vector<Pixel*> s = sort_pixels(ctx);

  ASSERT_EQ(4, s.size());

  for(int i = 1; i <= 4; i++) {
    EXPECT_EQ(i*10, s[i-1]->getData()[0]);
  }

}

TEST(GravityFloat, ArgSortixels) {
  InterpolationContext ctx;
  ctx.a = new PixelMono(40);
  ctx.b = new PixelMono(30);
  ctx.c = new PixelMono(20);
  ctx.d = new PixelMono(10);

  std::vector<int> s = arg_sort_pixels(ctx);

  ASSERT_EQ(4, s.size());

  for(int i = 0; i < 4; i++) {
    EXPECT_EQ(3-i, s[i]);
  }
}

TEST(GravityFloat, DiffPixelArrAllEqual) {
  PixelArr pixels;
  pixels.push_back(new PixelMono(10));
  pixels.push_back(new PixelMono(10));
  pixels.push_back(new PixelMono(10));
  pixels.push_back(new PixelMono(10));

  std::vector<unsigned char> diffs = diff_pixels(pixels);

  ASSERT_EQ(3, diffs.size());

  for(int i = 0; i < 3; i++) {
    EXPECT_EQ(0, diffs[i]);
  }
}

TEST(GravityFloat, MaximumJump) {
  PixelArr pixels;
  pixels.push_back(new PixelMono(10));
  pixels.push_back(new PixelMono(20));
  pixels.push_back(new PixelMono(40));
  pixels.push_back(new PixelMono(70));

  std::vector<unsigned char> diffs = diff_pixels(pixels);

  int Dmax, Kmax;
  maximum_jump(diffs, Dmax, Kmax);

  ASSERT_NE(-1, Dmax);
  ASSERT_NE(-1, Kmax);

  ASSERT_EQ(30, Dmax);
  ASSERT_EQ(2, Kmax);
}

TEST(GravityFloat, GetChoiceOfCase) {
  FAIL() << "finish the test";
}
