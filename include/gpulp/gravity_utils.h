#ifndef GPULP_GRAVITY_UTILS_H
#define GPULP_GRAVITY_UTILS_H

#include "gpulp/gpulp_utils.h"
#include "gpulp/InterpolationContext.h"
#include <vector>

namespace gpulp {
  typedef std::vector<Pixel*> PixelArr;

  struct GravityContext {
    InterpolationContext interpolationCtx;
    int Dmax; // value of max diff
    int Kmax; // idx of max diff
    std::vector<int> Nmax; // sorted indexes
    std::vector<float> dst;
    int cas;
    std::vector<float> w;
  };

  PixelArr sort_pixels(InterpolationContext &ctx);
  std::vector<int> arg_sort_pixels(InterpolationContext &ctx);
  std::vector<float> get_gravity_distances(InterpolationContext &ctx);
  std::vector<unsigned char> diff_pixels(PixelArr &pixels);
  void maximum_jump(std::vector<unsigned char> &diffs, int &Dmax, int &Kmax);
  int get_choice_of_case(GravityContext &ctx);
  std::vector<float> get_weights(GravityContext &ctx);
  std::vector<float> normalize_weights(std::vector<float> &w);
  GravityContext get_gravity_ctx(InterpolationContext &iCtx);
  PixelMono doInterpolation(InterpolationContext &ctx);
}

#endif