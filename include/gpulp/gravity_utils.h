#ifndef GPULP_GRAVITY_UTILS_H
#define GPULP_GRAVITY_UTILS_H

#include "gpulp/gpulp_utils.h"
#include "gpulp/InterpolationContext.h"
// #include <vector>
#include "gpulp/fixed_point.h"

namespace gpulp {
  class GravityContext {
  public:
    int Dmax; // value of max diff
    int Kmax; // idx of max diff
    int Nmax[4]; // sorted indexes
    int cas;
    Pixel* pixels[4];
    unsigned char diffs[3];

    void pixel_pair_sort();
    int get_choice_of_case();
    void diff_pixels();
    void maximum_jump();
    void common_init();

    virtual void set_gravity_distances() = 0;
    virtual void set_weights() = 0;
    virtual void normalize_weights() = 0;
  };

  class GravityContextFloat : public GravityContext {
    public:
      GravityContextFloat() {}
      GravityContextFloat(InterpolationContextFloat &iCtx);

      InterpolationContextFloat interpolationCtx;
      float dst[4];
      float w[4];

      void set_gravity_distances();
      void set_weights();
      void normalize_weights();
  };

  class GravityContextFixed : public GravityContext {
    public:
      GravityContextFixed() {}
      GravityContextFixed(InterpolationContextFixed &iCtx);

      InterpolationContextFixed interpolationCtx;
      FPNum dst[4];
      FPNum w[4];

      void set_gravity_distances();
      void set_weights();
      void normalize_weights();
  };
}

#endif
