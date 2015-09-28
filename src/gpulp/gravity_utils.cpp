#include "gpulp/gravity_utils.h"
#include <deque>
#include <cmath>

using namespace gpulp;
typedef std::pair<Pixel*, int> PixelPair;
typedef std::deque<PixelPair> PixelPairArr;

void GravityContext::common_init(PixelArr &input) {
  set_gravity_distances();

  sorted = sort_pixels(input);
  diffs = diff_pixels(sorted);
  maximum_jump(diffs);

  Nmax = arg_sort_pixels(input);
  cas = get_choice_of_case();

  set_weights();
  normalize_weights();
}

PixelPairArr pixel_pair_sort(PixelArr &pixels){
  PixelPairArr sorted;
  PixelPairArr firstHalf;
  PixelPairArr secondHalf;

  firstHalf.push_back(PixelPair(pixels[0], 0));
  firstHalf.push_back(PixelPair(pixels[1], 1));

  secondHalf.push_back(PixelPair(pixels[2], 2));
  secondHalf.push_back(PixelPair(pixels[3], 3));

  if(firstHalf[0].first->getData()[0] > firstHalf[1].first->getData()[0]) {
    firstHalf.push_back(firstHalf[0]);
    firstHalf.pop_front();
  }

  if(secondHalf[0].first->getData()[0] > secondHalf[1].first->getData()[0]) {
    secondHalf.push_back(secondHalf[0]);
    secondHalf.pop_front();
  }

  for(int i = 0; i < 4; i++) {
    if(firstHalf.size() && secondHalf.size()) {
      if(firstHalf.front().first->getData()[0] <
          secondHalf.front().first->getData()[0]) {
        sorted.push_back(firstHalf.front());
        firstHalf.pop_front();
      }
      else {
        sorted.push_back(secondHalf.front());
        secondHalf.pop_front();
      }
    }
    else if(firstHalf.size()) {
      sorted.push_back(firstHalf.front());
      firstHalf.pop_front();
    }
    else if(secondHalf.size()) {
      sorted.push_back(secondHalf.front());
      secondHalf.pop_front();
    }
  }

  return sorted;
}

PixelArr GravityContext::sort_pixels(PixelArr &input) {
  std::vector<Pixel*> parr;
  PixelPairArr pairs = pixel_pair_sort(input);

  for(int i = 0; i < 4 && i < pairs.size(); i++) {
    parr.push_back(pairs[i].first);
  }

  return parr;
}

std::vector<int> GravityContext::arg_sort_pixels(PixelArr &input) {
  std::vector<int> args;
  PixelPairArr pairs = pixel_pair_sort(input);

  for(int i = 0; i < 4 && i < pairs.size(); i++) {
    args.push_back(pairs[i].second);
  }

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

PixelMono gpulp::doInterpolation(InterpolationContextFloat &iCtx) {
  GravityContextFloat ctx(iCtx);

  unsigned char val;
  val += ctx.w[0]*ctx.interpolationCtx.a->getData()[0];
  val += ctx.w[1]*ctx.interpolationCtx.b->getData()[0];
  val += ctx.w[2]*ctx.interpolationCtx.c->getData()[0];
  val += ctx.w[3]*ctx.interpolationCtx.d->getData()[0];

  return PixelMono(val);
}
