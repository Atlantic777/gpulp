#include "gpulp/fixed_point.h"
#include <cstdio>

using namespace gpulp;

FPNum gpulp::to_fixed(float f) {
  uint32_t h = floor(f)*SCALING_FACTOR;
  uint32_t l = (uint32_t)((f-floor(f))*SCALING_FACTOR);

  return h + l;
}

float gpulp::from_fixed(FPNum f) {
  float rh =        (f & H_MASK)/SCALING_FACTOR;
  float rl = (float)(f & L_MASK)/SCALING_FACTOR;

  return rh + rl;
}

FPNum gpulp::mul(FPNum a, FPNum b) {
  uint64_t m   = (uint64_t)a*b;
  uint32_t mh  = (m & HH_MASK) >> H_BITS;
  uint32_t ml  = (m & H_MASK)  >> L_BITS;
  uint32_t res =  mh + ml;

  return res;
}
