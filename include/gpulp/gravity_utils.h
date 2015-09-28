#ifndef GPULP_GRAVITY_UTILS_H
#define GPULP_GRAVITY_UTILS_H

#include "gpulp/gpulp_utils.h"
#include "gpulp/InterpolationContext.h"
#include <vector>
#include "gpulp/fixed_point.h"

namespace gpulp {
  typedef std::vector<Pixel*> PixelArr;

  class GravityContext {
  public:
    int Dmax; // value of max diff
    int Kmax; // idx of max diff
    std::vector<int> Nmax; // sorted indexes
    int cas;
    PixelArr sorted;
    std::vector<unsigned char> diffs;

    int get_choice_of_case();
    PixelArr sort_pixels(PixelArr &input);
    std::vector<int> arg_sort_pixels(PixelArr &input);
    std::vector<unsigned char> diff_pixels(PixelArr &pixels);
    void maximum_jump(std::vector<unsigned char> &diffs);
    void common_init(PixelArr &input);
  };

  class GravityContextFloat : public GravityContext {
    public:
      GravityContextFloat() {}
      GravityContextFloat(InterpolationContextFloat &iCtx);
      InterpolationContextFloat interpolationCtx;
      std::vector<float> dst;
      std::vector<float> w;

      std::vector<float> get_gravity_distances();
      std::vector<float> get_weights();
      std::vector<float> normalize_weights();
  };

  // independant
  // PixelArr sort_pixels(PixelArr &input);
  // std::vector<int> arg_sort_pixels(PixelArr &input);
  // std::vector<unsigned char> diff_pixels(PixelArr &pixels);
  // void maximum_jump(std::vector<unsigned char> &diffs, int &Dmax, int &Kmax);

  // constructors
  // GravityContextFloat get_gravity_ctx(InterpolationContextFloat &iCtx);

  // float point
  // std::vector<float> get_gravity_distances(InterpolationContextFloat &ctx);
  // std::vector<float> get_weights(GravityContextFloat &ctx);
  // std::vector<float> normalize_weights(std::vector<float> &w);

  // fixed point
  // std::vector<FPNum> get_gravity_distances(InterpolationContextFloat &ctx);
  // std::vector<FPNum> get_weights(GravityContextFloat &ctx);
  // std::vector<FPNum> normalize_weights(std::vector<float> &w);

  // move out of here
  PixelMono doInterpolation(InterpolationContextFloat &ctx);

  // float lib dependant
  // --------------------
  // get_gravity_distances
  // get_weights
  // normalize_weigths - division, important!
  //
  // of course, doInterpolation() too
  // std::vector<FPNum> get_gravity_distances(InterpolationContextFixed &ctx);
}

#endif
