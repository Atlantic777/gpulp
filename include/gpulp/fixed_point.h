#ifndef GPULP_FIXED_POINT_H
#define GPULP_FIXED_POINT_H

#include <cstdint>
#include <cmath>

#define SCALING_FACTOR (1 << 16)
#define H_MASK  0xFFFF0000
#define L_MASK  0xFFFF
#define HH_MASK 0xFFFFFFFF00000000
#define L_BITS 16
#define H_BITS 16

namespace gpulp {
  typedef uint32_t FPNum;
  FPNum to_fixed(float a);
  float from_fixed(FPNum);
  FPNum mul(FPNum a, FPNum b);
}

#endif
