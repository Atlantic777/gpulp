#include "gtest/gtest.h"
#include "gpulp/fixed_point.h"

using namespace gpulp;

TEST(FixedPoint, ToFixedPoint) {
  FPNum n;

  n = to_fixed(0);
  ASSERT_EQ(0, n);

  n = to_fixed(0.75);
  ASSERT_EQ(3 << 14, n);

  n = to_fixed(1);
  ASSERT_EQ(1 << 16, n);
}

TEST(FixedPoint, FromFixedPoint) {
  FPNum n = 1 << 15;
  float f;

  f = from_fixed(n);
  ASSERT_EQ(0.5, f);
}

TEST(FixedPoinnt, FixedPointMultiplication) {
  FPNum a = to_fixed(4.25);
  FPNum b = to_fixed(4.25);

  FPNum fixed_result = mul(a, b);

  float float_result = from_fixed(fixed_result);
  float expected = 4.25*4.25;

  ASSERT_FLOAT_EQ(expected, float_result);
}
