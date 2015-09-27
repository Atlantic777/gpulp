#ifndef GPULP_INTERPOLATION_CONTEXT_H
#define GPULP_INTERPOLATION_CONTEXT_H

#include "gpulp/gpulp_utils.h"
#include "gpulp/fixed_point.h"

namespace gpulp {
struct InterpolationContextFloat {
  Pixel *a;
  Pixel *b;
  Pixel *c;
  Pixel *d;

  float dx;
  float dy;
};

struct InterpolationContextFixed {
  Pixel *a;
  Pixel *b;
  Pixel *c;
  Pixel *d;

  FPNum dx;
  FPNum dy;
};
}

#endif
