#include "gtest/gtest.h"
#include "gpulp/gravity_utils.h"
#include "gpulp/InterpolationContext.h"

using namespace gpulp;

TEST(GravityFloat, GetGravityDistances) {
  InterpolationContext ctx;
  ctx.dx = 0.2;
  ctx.dy = 0.4;

  std::vector<float> dst = get_gravity_distances(ctx);

  FAIL() << "finish test";
}

TEST(GravityFloat, SortPixels) {
  InterpolationContext ctx;
  std::vector<PixelMono> s = sort_pixels(ctx);

  FAIL() << "finish test";
}

TEST(GravityFloat, ArgSortixels) {
  InterpolationContext ctx;
  std::vector<int> args = arg_sort_pixels(ctx);

  FAIL() << "finish test";
}
