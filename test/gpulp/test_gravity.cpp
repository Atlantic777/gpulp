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
  std::vector<PixelMono> s = sort_pixels(ctx);

  FAIL() << "finish test";
}

TEST(GravityFloat, ArgSortixels) {
  InterpolationContext ctx;
  std::vector<int> args = arg_sort_pixels(ctx);

  FAIL() << "finish test";
}
