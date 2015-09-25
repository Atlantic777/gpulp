#include "gpulp/gravity_utils.h"
#include <cmath>

using namespace gpulp;

std::vector<PixelMono> gpulp::sort_pixels(InterpolationContext &ctx) {
  std::vector<PixelMono> parr;

  return parr;
}

std::vector<int> gpulp::arg_sort_pixels(InterpolationContext &ctx) {
  std::vector<int> args;

  return args;
}

std::vector<float> gpulp::get_gravity_distances(InterpolationContext &ctx) {
  std::vector<float> dst;

  dst.push_back(pow(ctx.dx, 2) + pow(ctx.dy, 2));
  dst.push_back(pow(1-ctx.dx, 2) + pow(ctx.dy, 2));
  dst.push_back(pow(ctx.dx, 2) + pow(1-ctx.dy, 2));
  dst.push_back(pow(1-ctx.dx, 2) + pow(1-ctx.dy, 2));

  return dst;
}
