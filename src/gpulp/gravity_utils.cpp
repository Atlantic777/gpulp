#include "gpulp/gravity_utils.h"
#include <deque>
#include <cmath>

using namespace gpulp;

void GravityContext::common_init() {
  set_gravity_distances();

  pixel_pair_sort();
  diff_pixels();
  maximum_jump();

  cas = get_choice_of_case();

  set_weights();
  normalize_weights();
}

void GravityContext::pixel_pair_sort(){
  int *index = Nmax;

  for(int i = 0; i < 4; i++) {
    Nmax[i] = i;
  }

  int a, b;
  int ti;

  a = 0;
  b = 2;
  if(pixels[a]->data[0] > pixels[b]->data[0]) {
    ti = index[a];
    index[a] = index[b];
    index[b] = ti;
  }

  a = 1;
  b = 3;
  if(pixels[a]->data[0] > pixels[b]->data[0]) {
    ti = index[a];
    index[a] = index[b];
    index[b] = ti;
  }

  a = 0;
  b = 1;
  if(pixels[a]->data[0] > pixels[b]->data[0]) {
    ti = index[a];
    index[a] = index[b];
    index[b] = ti;
  }

  a = 2;
  b = 3;
  if(pixels[a]->data[0] > pixels[b]->data[0]) {
    ti = index[a];
    index[a] = index[b];
    index[b] = ti;
  }

  a = 1;
  b = 2;
  if(pixels[a]->data[0] > pixels[b]->data[0]) {
    ti = index[a];
    index[a] = index[b];
    index[b] = ti;
  }

  Pixel *tp[4];
  for(int i = 0; i < 4; i++) {
    tp[i] = pixels[i];
  }

  for(int i = 0; i < 4; i++) {
    pixels[i] = tp[index[i]];
  }
}

void GravityContextFloat::set_gravity_distances() {
  InterpolationContextFloat &ctx = interpolationCtx;

  dst[0] = pow(ctx.dx, 2) + pow(ctx.dy, 2);
  dst[1] = pow(1-ctx.dx, 2) + pow(ctx.dy, 2);
  dst[2] = pow(ctx.dx, 2) + pow(1-ctx.dy, 2);
  dst[3] = pow(1-ctx.dx, 2) + pow(1-ctx.dy, 2);
}

void GravityContext::diff_pixels() {
  for(int i = 0; i < 3; i++) {
    diffs[i] = abs(pixels[i+1]->data[0] - pixels[i]->data[0]);
  }
}

void GravityContext::maximum_jump()  {
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
  interpolationCtx = iCtx;
  pixels[0] = iCtx.a;
  pixels[1] = iCtx.b;
  pixels[2] = iCtx.c;
  pixels[3] = iCtx.d;
  common_init();
}

GravityContextFixed::GravityContextFixed(InterpolationContextFixed &iCtx) {
  interpolationCtx = iCtx;
  pixels[0] = iCtx.a;
  pixels[1] = iCtx.b;
  pixels[2] = iCtx.c;
  pixels[3] = iCtx.d;
  common_init();
}

void GravityContextFixed::set_gravity_distances() {
  FPNum one = to_fixed(1);
  InterpolationContextFixed &ctx = interpolationCtx;

  dst[0] = mul(ctx.dx, ctx.dx) + mul(ctx.dy, ctx.dy);
  dst[1] = mul(one - ctx.dx, one - ctx.dx) + mul(ctx.dy, ctx.dy);
  dst[2] = mul(ctx.dx, ctx.dx) + mul(one - ctx.dy, one - ctx.dy);
  dst[3] = mul(one - ctx.dx, one - ctx.dx) + mul(one - ctx.dy, one - ctx.dy);
}

void GravityContextFixed::set_weights() {
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
