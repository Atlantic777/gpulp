#include "gpulp/gravity_utils.h"
#include <deque>
#include <cmath>

using namespace gpulp;
typedef std::pair<Pixel*, int> PixelPair;
typedef std::vector<PixelPair> PixelPairArr;

void GravityContext::common_init(PixelArr &input) {
  set_gravity_distances();

  pixel_pair_sort(input);
  // Nmax = arg_sort_pixels(input);
  // sorted = sort_pixels(input);
  diffs = diff_pixels(sorted);
  maximum_jump(diffs);

  cas = get_choice_of_case();

  set_weights();
  normalize_weights();
}

void GravityContext::pixel_pair_sort(PixelArr &pixels){
  int *index = Nmax;
  unsigned char value[4];

  for(int i = 0; i < 4; i++) {
    Nmax[i] = i;
    value[i] = pixels[i]->data[0];
  }

  int a, b;
  int ti;
  unsigned char tv;

  a = 0;
  b = 2;
  if(value[a] > value[b]) {
    ti = index[a];
    index[a] = index[b];
    index[b] = ti;

    tv = value[a];
    value[a] = value[b];
    value[b] = tv;
  }

  a = 1;
  b = 3;
  if(value[a] > value[b]) {
    ti = index[a];
    index[a] = index[b];
    index[b] = ti;

    tv = value[a];
    value[a] = value[b];
    value[b] = tv;
  }

  a = 0;
  b = 1;
  if(value[a] > value[b]) {
    ti = index[a];
    index[a] = index[b];
    index[b] = ti;

    tv = value[a];
    value[a] = value[b];
    value[b] = tv;
  }

  a = 2;
  b = 3;
  if(value[a] > value[b]) {
    ti = index[a];
    index[a] = index[b];
    index[b] = ti;

    tv = value[a];
    value[a] = value[b];
    value[b] = tv;
  }

  a = 1;
  b = 2;
  if(value[a] > value[b]) {
    ti = index[a];
    index[a] = index[b];
    index[b] = ti;

    tv = value[a];
    value[a] = value[b];
    value[b] = tv;
  }

  sorted.clear();
  for(int i = 0; i < 4; i++) {
    sorted.push_back(pixels[index[i]]);
  }

  // return index;
}

PixelArr GravityContext::sort_pixels(PixelArr &input) {
  std::vector<Pixel*> parr;
  // PixelPairArr pairs = pixel_pair_sort(input);
  //
  // for(int i = 0; i < 4; i++) {
  //   parr.push_back(pairs[i].first);
  // }

  return parr;
}

std::vector<int> GravityContext::arg_sort_pixels(PixelArr &input) {
  std::vector<int> args;
  // PixelPairArr pairs = pixel_pair_sort(input);
  //
  // for(int i = 0; i < 4; i++) {
  //   args.push_back(pairs[i].second);
  // }

  return args;
}

void GravityContextFloat::set_gravity_distances() {
  InterpolationContextFloat &ctx = interpolationCtx;

  dst.clear();
  dst.push_back(pow(ctx.dx, 2) + pow(ctx.dy, 2));
  dst.push_back(pow(1-ctx.dx, 2) + pow(ctx.dy, 2));
  dst.push_back(pow(ctx.dx, 2) + pow(1-ctx.dy, 2));
  dst.push_back(pow(1-ctx.dx, 2) + pow(1-ctx.dy, 2));
}

std::vector<unsigned char> GravityContext::diff_pixels(PixelArr &pixels) {
  std::vector<unsigned char> diffs;
  unsigned char tmp;

  for(int i = 0; i < 3; i++) {
    tmp = abs(pixels[i+1]->getData()[0] - pixels[i]->getData()[0]);
    diffs.push_back(tmp);
  }

  return diffs;
}

void GravityContext::maximum_jump(std::vector<unsigned char> &diffs)  {
  Dmax = -1;
  Kmax = -1;

  for(int i = 0; i < 3; i++) {
    if(diffs[i] > Dmax) {
      Dmax = diffs[i];
      Kmax = i;
    }
  }
}

int GravityContext::get_choice_of_case() {
  if(Dmax < 8) {
    cas = 7;
  }
  else if(Kmax == 0) {
    cas = Nmax[0];
  }
  else if(Kmax == 2) {
    cas = Nmax[3];
  }
  else {
    if((Nmax[0] == 0 && Nmax[1] == 1) ||
       (Nmax[0] == 2 && Nmax[1] == 3)) {
      cas = 5;
    }
    else if((Nmax[0] == 0 && Nmax[1] == 2) ||
            (Nmax[0] == 1 && Nmax[1] == 3)) {
      cas = 6;
    }
    else {
      cas = 7;
    }
  }

  return cas;
}

void GravityContextFloat::set_weights() {
  w = std::vector<float>(4, 0);
  if(cas == 0) {
    if(interpolationCtx.dy < (0.5 - interpolationCtx.dx)) {
      w[0] = 1;
    }
    else {
      w[1] = dst[2] * dst[3];
      w[2] = dst[1] * dst[3];
      w[3] = dst[1] * dst[2];
    }
  }
  else if(cas == 1) {
    if(interpolationCtx.dy < 0.5 - interpolationCtx.dx) {
      w[1] = 1;
    }
    else {
      w[0] = dst[2]*dst[3];
      w[2] = dst[0]*dst[3];
      w[3] = dst[0]*dst[2];
    }
  }
  else if(cas == 2) {
    if(interpolationCtx.dy > 0.5 + interpolationCtx.dx) {
      w[2] = 1;
    }
    else {
      w[0] = dst[1]*dst[3];
      w[1] = dst[0]*dst[3];
      w[3] = dst[0]*dst[1];
    }
  }
  else if(cas == 3) {
    if(interpolationCtx.dy > 1.5 - interpolationCtx.dx) {
      w[3] = 1;
    }
    else {
      w[0] = dst[1]*dst[2];
      w[1] = dst[0]*dst[2];
      w[2] = dst[0]*dst[1];
    }
  }
  else if(cas == 5) {
    if(interpolationCtx.dy < 0.5) {
      w[0] = dst[1];
      w[1] = dst[0];
    }
    else {
      w[2] = dst[3];
      w[3] = dst[2];
    }
  }
  else if(cas == 6) {
    if(interpolationCtx.dx < 0.5) {
      w[0] = dst[2];
      w[2] = dst[0];
    }
    else {
      w[1] = dst[3];
      w[3] = dst[1];
    }
  }
  else {
    w[0] = dst[1]*dst[2]*dst[3];
    w[1] = dst[0]*dst[2]*dst[3];
    w[2] = dst[0]*dst[1]*dst[3];
    w[3] = dst[0]*dst[1]*dst[2];
  }
}

void GravityContextFloat::normalize_weights() {
  float sum = 0;
  for(int i = 0; i < 4; i++) {
    sum += w[i];
  }

  for(int i = 0; i < 4; i++) {
    w[i] /= sum;
  }
}

GravityContextFloat::GravityContextFloat(InterpolationContextFloat &iCtx) {
  PixelArr input;
  input.push_back(iCtx.a);
  input.push_back(iCtx.b);
  input.push_back(iCtx.c);
  input.push_back(iCtx.d);

  interpolationCtx = iCtx;
  common_init(input);
}

GravityContextFixed::GravityContextFixed(InterpolationContextFixed &iCtx) {
  PixelArr input;
  input.push_back(iCtx.a);
  input.push_back(iCtx.b);
  input.push_back(iCtx.c);
  input.push_back(iCtx.d);

  interpolationCtx = iCtx;
  common_init(input);
}

void GravityContextFixed::set_gravity_distances() {
  FPNum one = to_fixed(1);
  InterpolationContextFixed &ctx = interpolationCtx;

  dst.clear();
  dst.push_back(mul(ctx.dx, ctx.dx) + mul(ctx.dy, ctx.dy));
  dst.push_back(mul(one - ctx.dx, one - ctx.dx) + mul(ctx.dy, ctx.dy));
  dst.push_back(mul(ctx.dx, ctx.dx) + mul(one - ctx.dy, one - ctx.dy));
  dst.push_back(mul(one - ctx.dx, one - ctx.dx) + mul(one - ctx.dy, one - ctx.dy));
}

void GravityContextFixed::set_weights() {
  w = std::vector<FPNum>(4, 0);

  if(cas == 0) {
    if(interpolationCtx.dy < (to_fixed(0.5) - interpolationCtx.dx)) {
      w[0] = to_fixed(1);
    }
    else {
      w[1] = mul(dst[2], dst[3]);
      w[2] = mul(dst[1], dst[3]);
      w[3] = mul(dst[1], dst[2]);
    }
  }
  else if(cas == 1) {
    if(interpolationCtx.dy < to_fixed(0.5) - interpolationCtx.dx) {
      w[1] = to_fixed(1);
    }
    else {
      w[0] = mul(dst[2],dst[3]);
      w[2] = mul(dst[0],dst[3]);
      w[3] = mul(dst[0],dst[2]);
    }
  }
  else if(cas == 2) {
    if(interpolationCtx.dy > to_fixed(0.5) + interpolationCtx.dx) {
      w[2] = to_fixed(1);
    }
    else {
      w[0] = mul(dst[1],dst[3]);
      w[1] = mul(dst[0],dst[3]);
      w[3] = mul(dst[0],dst[1]);
    }
  }
  else if(cas == 3) {
    if(interpolationCtx.dy > to_fixed(1.5) - interpolationCtx.dx) {
      w[3] = to_fixed(1);
    }
    else {
      w[0] = mul(dst[1],dst[2]);
      w[1] = mul(dst[0],dst[2]);
      w[2] = mul(dst[0],dst[1]);
    }
  }
  else if(cas == 5) {
    if(interpolationCtx.dy < to_fixed(0.5)) {
      w[0] = dst[1];
      w[1] = dst[0];
    }
    else {
      w[2] = dst[3];
      w[3] = dst[2];
    }
  }
  else if(cas == 6) {
    if(interpolationCtx.dx < to_fixed(0.5)) {
      w[0] = dst[2];
      w[2] = dst[0];
    }
    else {
      w[1] = dst[3];
      w[3] = dst[1];
    }
  }
  else {
    w[0] = mul(mul(dst[1], dst[2]) ,dst[3]);
    w[1] = mul(mul(dst[0], dst[2]), dst[3]);
    w[2] = mul(mul(dst[0], dst[1]), dst[3]);
    w[3] = mul(mul(dst[0], dst[1]), dst[2]);
  }
}

void GravityContextFixed::normalize_weights() {
  FPNum sum = 0;
  for(int i = 0; i < 4; i++) {
    sum += w[i];
  }

  for(int i = 0; i < 4; i++) {
    w[i] = (uint64_t(w[i]) << 32) / sum >> L_BITS;
  }
}
