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
  GravityContext ctx;
  ctx.Dmax = 2;
  ctx.Nmax.push_back(3);
  ctx.Nmax.push_back(2);
  ctx.Nmax.push_back(1);
  ctx.Nmax.push_back(0);

  int choice;

  choice = get_choice_of_case(ctx);
  ASSERT_EQ(7, choice);

  ctx.Dmax = 8;
  ctx.Kmax = 0;
  choice = get_choice_of_case(ctx);
  ASSERT_NE(7, choice);
  ASSERT_NE(-1, choice);
  ASSERT_EQ(3, choice);

  ctx.Kmax = 2;
  choice = get_choice_of_case(ctx);
  ASSERT_EQ(0, choice);

  ctx.Kmax = 1;
  ctx.Nmax[0] = 0;
  ctx.Nmax[1] = 1;
  choice = get_choice_of_case(ctx);
  ASSERT_EQ(5, choice);

  ctx.Nmax[0] = 2;
  ctx.Nmax[1] = 3;
  choice = get_choice_of_case(ctx);
  ASSERT_EQ(5, choice);

  ctx.Nmax[0] = 0;
  ctx.Nmax[1] = 2;
  choice = get_choice_of_case(ctx);
  ASSERT_EQ(6, choice);

  ctx.Nmax[0] = 1;
  ctx.Nmax[1] = 3;
  choice = get_choice_of_case(ctx);
  ASSERT_EQ(6, choice);

  ctx.Kmax = 3;
  ctx.Nmax[0] = 0;
  ctx.Nmax[1] = 3;
  choice = get_choice_of_case(ctx);
  ASSERT_EQ(7, choice);
}

TEST(GravityFloat, GetInterpolationCoeffs) {
  GravityContext ctx;

  ctx.cas = 0;
  ctx.interpolationCtx.dx = 0.2;
  ctx.interpolationCtx.dy = 0.1;

  std::vector<float> w = get_weights(ctx);
  ASSERT_EQ(4, w.size());
  ASSERT_FLOAT_EQ(1, w[0]);
  ASSERT_FLOAT_EQ(0, w[1]);
  ASSERT_FLOAT_EQ(0, w[2]);
  ASSERT_FLOAT_EQ(0, w[3]);

  ctx.interpolationCtx.dy = 0.5;
  ctx.dst = get_gravity_distances(ctx.interpolationCtx);
  w = get_weights(ctx);

  ASSERT_FLOAT_EQ(0, w[0]);
  ASSERT_FLOAT_EQ(0.29*0.89, w[1]);
  ASSERT_FLOAT_EQ(0.89*0.89, w[2]);
  ASSERT_FLOAT_EQ(0.89*0.29, w[3]);

  ctx.cas = 1;
  ctx.interpolationCtx.dy = 0.1;
  w = get_weights(ctx);
  ASSERT_FLOAT_EQ(0, w[0]);
  ASSERT_FLOAT_EQ(1, w[1]);
  ASSERT_FLOAT_EQ(0, w[2]);
  ASSERT_FLOAT_EQ(0, w[3]);

  ctx.interpolationCtx.dy = 0.5;
  ctx.dst = get_gravity_distances(ctx.interpolationCtx);
  w = get_weights(ctx);
  ASSERT_FLOAT_EQ(0.29*0.89, w[0]);
  ASSERT_FLOAT_EQ(0, w[1]);
  ASSERT_FLOAT_EQ(0.29*0.89, w[2]);
  ASSERT_FLOAT_EQ(0.29*0.29, w[3]);

  ctx.cas = 2;
  ctx.interpolationCtx.dy = 0.9;
  w = get_weights(ctx);
  ASSERT_FLOAT_EQ(0, w[0]);
  ASSERT_FLOAT_EQ(0, w[1]);
  ASSERT_FLOAT_EQ(1, w[2]);
  ASSERT_FLOAT_EQ(0, w[3]);

  ctx.interpolationCtx.dy = 0.5;
  ctx.dst = get_gravity_distances(ctx.interpolationCtx);
  w = get_weights(ctx);
  ASSERT_FLOAT_EQ(0.89*0.89, w[0]);
  ASSERT_FLOAT_EQ(0.29*0.89, w[1]);
  ASSERT_FLOAT_EQ(0, w[2]);
  ASSERT_FLOAT_EQ(0.29*0.89, w[3]);

  ctx.cas = 3;
  ctx.interpolationCtx.dx = 1;
  ctx.interpolationCtx.dy = 0.7;
  w = get_weights(ctx);
  ASSERT_FLOAT_EQ(0, w[0]);
  ASSERT_FLOAT_EQ(0, w[1]);
  ASSERT_FLOAT_EQ(0, w[2]);
  ASSERT_FLOAT_EQ(1, w[3]);

  ctx.interpolationCtx.dx = 0.2;
  ctx.interpolationCtx.dy = 0.5;
  ctx.dst = get_gravity_distances(ctx.interpolationCtx);
  w = get_weights(ctx);
  ASSERT_FLOAT_EQ(0.89*0.29, w[0]);
  ASSERT_FLOAT_EQ(0.29*0.29, w[1]);
  ASSERT_FLOAT_EQ(0.29*0.89, w[2]);
  ASSERT_FLOAT_EQ(0, w[3]);

  ctx.cas = 5;
  ctx.interpolationCtx.dy = 0.2;
  ctx.dst = get_gravity_distances(ctx.interpolationCtx);
  w = get_weights(ctx);
  ASSERT_FLOAT_EQ(0.68, w[0]);
  ASSERT_FLOAT_EQ(0.08, w[1]);
  ASSERT_FLOAT_EQ(0, w[2]);
  ASSERT_FLOAT_EQ(0, w[3]);

  ctx.interpolationCtx.dy = 0.8;
  ctx.dst = get_gravity_distances(ctx.interpolationCtx);
  w = get_weights(ctx);
  ASSERT_FLOAT_EQ(0, w[0]);
  ASSERT_FLOAT_EQ(0, w[1]);
  ASSERT_FLOAT_EQ(0.68, w[2]);
  ASSERT_FLOAT_EQ(0.08, w[3]);

  ctx.cas = 6;
  ctx.interpolationCtx.dx = 0.2;
  ctx.interpolationCtx.dy = 0.5;
  ctx.dst = get_gravity_distances(ctx.interpolationCtx);
  w = get_weights(ctx);
  ASSERT_FLOAT_EQ(0.29, w[0]);
  ASSERT_FLOAT_EQ(0, w[1]);
  ASSERT_FLOAT_EQ(0.29, w[2]);
  ASSERT_FLOAT_EQ(0, w[3]);

  ctx.interpolationCtx.dx = 0.8;
  ctx.dst = get_gravity_distances(ctx.interpolationCtx);
  w = get_weights(ctx);
  ASSERT_FLOAT_EQ(0, w[0]);
  ASSERT_FLOAT_EQ(0.29, w[1]);
  ASSERT_FLOAT_EQ(0, w[2]);
  ASSERT_FLOAT_EQ(0.29, w[3]);

  ctx.cas = 7;
  w = get_weights(ctx);
  ASSERT_FLOAT_EQ(0.29*0.89*0.29, w[0]);
  ASSERT_FLOAT_EQ(0.89*0.89*0.29, w[1]);
  ASSERT_FLOAT_EQ(0.89*0.29*0.29, w[2]);
  ASSERT_FLOAT_EQ(0.89*0.29*0.89, w[3]);
}

TEST(GravityFloat, NormalizeWeights) {
  std::vector<float> w(4, 1);
  normalize_weights(w);

  for(int i = 0; i < 4; i++) {
    ASSERT_EQ(0.25, w[i]);
  }
}
