#ifndef GPULP_INTERPOLATION_CONTEXT_H
#define GPULP_INTERPOLATION_CONTEXT_H

#include "gpulp/gpulp_utils.h"

namespace gpulp {
struct InterpolationContext {
  Pixel *a;
  Pixel *b;
  Pixel *c;
  Pixel *d;

  float dx;
  float dy;
};
}

#endif
