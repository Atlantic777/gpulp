#ifndef GPULP_GRAVITY_UTILS_H
#define GPULP_GRAVITY_UTILS_H

#include "gpulp/gpulp_utils.h"
#include "gpulp/InterpolationContext.h"
#include <vector>

namespace gpulp {
  std::vector<PixelMono> sort_pixels(InterpolationContext &ctx);
  std::vector<int> arg_sort_pixels(InterpolationContext &ctx);
  std::vector<float> get_gravity_distances(InterpolationContext &ctx);
}

#endif
