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

    virtual void set_gravity_distances() = 0;
    virtual void set_weights() = 0;
    virtual void normalize_weights() = 0;
  };

  class GravityContextFloat : public GravityContext {
    public:
      GravityContextFloat() {}
      GravityContextFloat(InterpolationContextFloat &iCtx);

      InterpolationContextFloat interpolationCtx;
      std::vector<float> dst;
      std::vector<float> w;

      void set_gravity_distances();
      void set_weights();
      void normalize_weights();
  };

  class GravityContextFixed : public GravityContext {
    public:
      GravityContextFixed() {}
      GravityContextFixed(InterpolationContextFixed &iCtx);

      InterpolationContextFixed interpolationCtx;
      std::vector<FPNum> dst;
      std::vector<FPNum> w;

      void set_gravity_distances();
      void set_weights();
      void normalize_weights();
  };

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
