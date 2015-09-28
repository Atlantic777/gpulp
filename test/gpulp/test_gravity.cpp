#include "gtest/gtest.h"
#include "gpulp/gravity_utils.h"
#include "gpulp/InterpolationContext.h"

using namespace gpulp;

InterpolationContextFloat get_iCtx() {
  InterpolationContextFloat iCtx;
  iCtx.a = new PixelMono(40);
  iCtx.b = new PixelMono(30);
  iCtx.c = new PixelMono(20);
  iCtx.d = new PixelMono(10);

  iCtx.dx = 0.2;
  iCtx.dy = 0.4;

  return iCtx;
}

TEST(GravityFloat, GetGravityDistances) {
  InterpolationContextFloat iCtx = get_iCtx();

  GravityContextFloat ctx(iCtx);
  std::vector<float> &dst = ctx.dst;

  ASSERT_EQ(4, dst.size());

  ASSERT_FLOAT_EQ(0.04 + 0.16, dst[0]); // top left
  ASSERT_FLOAT_EQ(0.64 + 0.16, dst[1]); // top right
  ASSERT_FLOAT_EQ(0.04 + 0.36, dst[2]); // bottom left
  ASSERT_FLOAT_EQ(0.64 + 0.36, dst[3]); // bottom right
}

TEST(GravityFloat, SortPixels) {
  InterpolationContextFloat iCtx = get_iCtx();
  GravityContextFloat ctx(iCtx);

  ASSERT_EQ(4, ctx.sorted.size());

  for(int i = 1; i <= 4; i++) {
    EXPECT_EQ(i*10, ctx.sorted[i-1]->getData()[0]);
  }
}

TEST(GravityFloat, ArgSortPixels) {
  InterpolationContextFloat iCtx = get_iCtx();
  GravityContextFloat ctx(iCtx);

  ASSERT_EQ(4, ctx.Nmax.size());

  for(int i = 0; i < 4; i++) {
    EXPECT_EQ(3-i, ctx.Nmax[i]);
  }
}

TEST(GravityFloat, DiffPixelArrAllEqual) {
  InterpolationContextFloat iCtx;
  iCtx.a = new PixelMono(0);
  iCtx.b = new PixelMono(0);
  iCtx.c = new PixelMono(0);
  iCtx.d = new PixelMono(0);
  GravityContextFloat ctx(iCtx);

  ASSERT_EQ(3, ctx.diffs.size());

  for(int i = 0; i < 3; i++) {
    EXPECT_EQ(0, ctx.diffs[i]);
  }
}

TEST(GravityFloat, MaximumJump) {
  InterpolationContextFloat iCtx;
  iCtx.a = new PixelMono(10);
  iCtx.b = new PixelMono(20);
  iCtx.c = new PixelMono(40);
  iCtx.d = new PixelMono(70);

  GravityContextFloat ctx(iCtx);

  ASSERT_NE(-1, ctx.Dmax);
  ASSERT_NE(-1, ctx.Kmax);

  ASSERT_EQ(30, ctx.Dmax);
  ASSERT_EQ(2, ctx.Kmax);
}

TEST(GravityFloat, GetChoiceOfCase) {
  GravityContextFloat ctx;

  ctx.Dmax = 2;
  ctx.Nmax.push_back(3);
  ctx.Nmax.push_back(2);
  ctx.Nmax.push_back(1);
  ctx.Nmax.push_back(0);

  int choice;
  choice = ctx.get_choice_of_case();
  ASSERT_EQ(7, choice);

  ctx.Dmax = 8;
  ctx.Kmax = 0;
  choice = ctx.get_choice_of_case();
  ASSERT_NE(7, choice);
  ASSERT_NE(-1, choice);
  ASSERT_EQ(3, choice);

  ctx.Kmax = 2;
  choice = ctx.get_choice_of_case();
  ASSERT_EQ(0, choice);

  ctx.Kmax = 1;
  ctx.Nmax[0] = 0;
  ctx.Nmax[1] = 1;
  choice = ctx.get_choice_of_case();
  ASSERT_EQ(5, choice);

  ctx.Nmax[0] = 2;
  ctx.Nmax[1] = 3;
  choice = ctx.get_choice_of_case();
  ASSERT_EQ(5, choice);

  ctx.Nmax[0] = 0;
  ctx.Nmax[1] = 2;
  choice = ctx.get_choice_of_case();
  ASSERT_EQ(6, choice);

  ctx.Nmax[0] = 1;
  ctx.Nmax[1] = 3;
  choice = ctx.get_choice_of_case();
  ASSERT_EQ(6, choice);

  ctx.Kmax = 3;
  ctx.Nmax[0] = 0;
  ctx.Nmax[1] = 3;
  choice = ctx.get_choice_of_case();
  ASSERT_EQ(7, choice);
}

TEST(GravityFloat, GetInterpolationCoeffs) {
  GravityContextFloat ctx;

  ctx.cas = 0;
  ctx.interpolationCtx.dx = 0.2;
  ctx.interpolationCtx.dy = 0.1;

  ctx.set_weights();
  std::vector<float> &w = ctx.w;
  ASSERT_EQ(4, w.size());
  ASSERT_FLOAT_EQ(1, w[0]);
  ASSERT_FLOAT_EQ(0, w[1]);
  ASSERT_FLOAT_EQ(0, w[2]);
  ASSERT_FLOAT_EQ(0, w[3]);

  ctx.interpolationCtx.dy = 0.5;
  ctx.set_gravity_distances();
  ctx.set_weights();

  ASSERT_FLOAT_EQ(0, w[0]);
  ASSERT_FLOAT_EQ(0.29*0.89, w[1]);
  ASSERT_FLOAT_EQ(0.89*0.89, w[2]);
  ASSERT_FLOAT_EQ(0.89*0.29, w[3]);

  ctx.cas = 1;
  ctx.interpolationCtx.dy = 0.1;
  ctx.set_weights();
  ASSERT_FLOAT_EQ(0, w[0]);
  ASSERT_FLOAT_EQ(1, w[1]);
  ASSERT_FLOAT_EQ(0, w[2]);
  ASSERT_FLOAT_EQ(0, w[3]);

  ctx.interpolationCtx.dy = 0.5;
  ctx.set_gravity_distances();
  ctx.set_weights();
  ASSERT_FLOAT_EQ(0.29*0.89, w[0]);
  ASSERT_FLOAT_EQ(0, w[1]);
  ASSERT_FLOAT_EQ(0.29*0.89, w[2]);
  ASSERT_FLOAT_EQ(0.29*0.29, w[3]);

  ctx.cas = 2;
  ctx.interpolationCtx.dy = 0.9;
  ctx.set_weights();
  ASSERT_FLOAT_EQ(0, w[0]);
  ASSERT_FLOAT_EQ(0, w[1]);
  ASSERT_FLOAT_EQ(1, w[2]);
  ASSERT_FLOAT_EQ(0, w[3]);

  ctx.interpolationCtx.dy = 0.5;
  ctx.set_gravity_distances();
  ctx.set_weights();
  ASSERT_FLOAT_EQ(0.89*0.89, w[0]);
  ASSERT_FLOAT_EQ(0.29*0.89, w[1]);
  ASSERT_FLOAT_EQ(0, w[2]);
  ASSERT_FLOAT_EQ(0.29*0.89, w[3]);

  ctx.cas = 3;
  ctx.interpolationCtx.dx = 1;
  ctx.interpolationCtx.dy = 0.7;
  ctx.set_weights();
  ASSERT_FLOAT_EQ(0, w[0]);
  ASSERT_FLOAT_EQ(0, w[1]);
  ASSERT_FLOAT_EQ(0, w[2]);
  ASSERT_FLOAT_EQ(1, w[3]);

  ctx.interpolationCtx.dx = 0.2;
  ctx.interpolationCtx.dy = 0.5;
  ctx.set_gravity_distances();
  ctx.set_weights();
  ASSERT_FLOAT_EQ(0.89*0.29, w[0]);
  ASSERT_FLOAT_EQ(0.29*0.29, w[1]);
  ASSERT_FLOAT_EQ(0.29*0.89, w[2]);
  ASSERT_FLOAT_EQ(0, w[3]);

  ctx.cas = 5;
  ctx.interpolationCtx.dy = 0.2;
  ctx.set_gravity_distances();
  ctx.set_weights();
  ASSERT_FLOAT_EQ(0.68, w[0]);
  ASSERT_FLOAT_EQ(0.08, w[1]);
  ASSERT_FLOAT_EQ(0, w[2]);
  ASSERT_FLOAT_EQ(0, w[3]);

  ctx.interpolationCtx.dy = 0.8;
  ctx.set_gravity_distances();
  ctx.set_weights();
  ASSERT_FLOAT_EQ(0, w[0]);
  ASSERT_FLOAT_EQ(0, w[1]);
  ASSERT_FLOAT_EQ(0.68, w[2]);
  ASSERT_FLOAT_EQ(0.08, w[3]);

  ctx.cas = 6;
  ctx.interpolationCtx.dx = 0.2;
  ctx.interpolationCtx.dy = 0.5;
  ctx.set_gravity_distances();
  ctx.set_weights();
  ASSERT_FLOAT_EQ(0.29, w[0]);
  ASSERT_FLOAT_EQ(0, w[1]);
  ASSERT_FLOAT_EQ(0.29, w[2]);
  ASSERT_FLOAT_EQ(0, w[3]);

  ctx.interpolationCtx.dx = 0.8;
  ctx.set_gravity_distances();
  ctx.set_weights();
  ASSERT_FLOAT_EQ(0, w[0]);
  ASSERT_FLOAT_EQ(0.29, w[1]);
  ASSERT_FLOAT_EQ(0, w[2]);
  ASSERT_FLOAT_EQ(0.29, w[3]);

  ctx.cas = 7;
  ctx.set_weights();
  ASSERT_FLOAT_EQ(0.29*0.89*0.29, w[0]);
  ASSERT_FLOAT_EQ(0.89*0.89*0.29, w[1]);
  ASSERT_FLOAT_EQ(0.89*0.29*0.29, w[2]);
  ASSERT_FLOAT_EQ(0.89*0.29*0.89, w[3]);
}

TEST(GravityFloat, NormalizeWeights) {
  GravityContextFloat ctx;
  std::vector<float> w(4, 1);
  ctx.w = w;
  ctx.normalize_weights();

  for(int i = 0; i < 4; i++) {
    ASSERT_EQ(0.25, ctx.w[i]);
  }
}

TEST(GravityFloat, PrepareGravityCtx) {
  InterpolationContextFloat iCtx;

  iCtx.a = new PixelMono(255);
  iCtx.b = new PixelMono(0);
  iCtx.c = new PixelMono(0);
  iCtx.d = new PixelMono(0);

  iCtx.dx = 0.2;
  iCtx.dy = 0.2;

  GravityContextFloat ctx(iCtx);
  ASSERT_FLOAT_EQ(0.08, ctx.dst[0]);
  ASSERT_FLOAT_EQ(0.68, ctx.dst[1]);
  ASSERT_FLOAT_EQ(0.68, ctx.dst[2]);
  ASSERT_FLOAT_EQ(1.28, ctx.dst[3]);

  ASSERT_EQ(255, ctx.Dmax);
  ASSERT_EQ(2, ctx.Kmax);

  ASSERT_EQ(0, ctx.Nmax[3]);
  ASSERT_EQ(0, ctx.cas);

  ASSERT_FLOAT_EQ(1, ctx.w[0]);
  ASSERT_FLOAT_EQ(0, ctx.w[1]);
  ASSERT_FLOAT_EQ(0, ctx.w[2]);
  ASSERT_FLOAT_EQ(0, ctx.w[3]);
}

TEST(GravityFloat, DoInterpolation) {
  InterpolationContextFloat iCtx;
  iCtx.a = new PixelMono(255);
  iCtx.b = new PixelMono(0);
  iCtx.c = new PixelMono(0);
  iCtx.d = new PixelMono(0);
  iCtx.dx = 0.2;
  iCtx.dy = 0.2;

  PixelMono p = doInterpolation(iCtx);
  ASSERT_EQ(255, p.getData()[0]);
}
