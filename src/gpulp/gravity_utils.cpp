#include "gpulp/gravity_utils.h"
#include <deque>
#include <cmath>

using namespace gpulp;
typedef std::pair<Pixel*, int> PixelPair;
typedef std::deque<PixelPair> PixelPairArr;

PixelPairArr pixel_pair_sort(InterpolationContextFloat &ctx){
  PixelPairArr sorted;
  PixelPairArr firstHalf;
  PixelPairArr secondHalf;

  firstHalf.push_back(PixelPair(ctx.a, 0));
  firstHalf.push_back(PixelPair(ctx.b, 1));

  secondHalf.push_back(PixelPair(ctx.c, 2));
  secondHalf.push_back(PixelPair(ctx.d, 3));

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

PixelArr gpulp::sort_pixels(InterpolationContextFloat &ctx) {
  std::vector<Pixel*> parr;
  PixelPairArr pairs = pixel_pair_sort(ctx);

  for(int i = 0; i < 4 && i < pairs.size(); i++) {
    parr.push_back(pairs[i].first);
  }

  return parr;
}

std::vector<int> gpulp::arg_sort_pixels(InterpolationContextFloat &ctx) {
  std::vector<int> args;
  PixelPairArr pairs = pixel_pair_sort(ctx);

  for(int i = 0; i < 4 && i < pairs.size(); i++) {
    args.push_back(pairs[i].second);
  }

  return args;
}

std::vector<float> gpulp::get_gravity_distances(InterpolationContextFloat &ctx) {
  std::vector<float> dst;

  dst.push_back(pow(ctx.dx, 2) + pow(ctx.dy, 2));
  dst.push_back(pow(1-ctx.dx, 2) + pow(ctx.dy, 2));
  dst.push_back(pow(ctx.dx, 2) + pow(1-ctx.dy, 2));
  dst.push_back(pow(1-ctx.dx, 2) + pow(1-ctx.dy, 2));

  return dst;
}

std::vector<unsigned char> gpulp::diff_pixels(PixelArr &pixels) {
  std::vector<unsigned char> diffs;
  unsigned char tmp;

  for(int i = 0; i < 3; i++) {
    tmp = abs(pixels[i+1]->getData()[0] - pixels[i]->getData()[0]);
    diffs.push_back(tmp);
  }

  return diffs;
}

void gpulp::maximum_jump(std::vector<unsigned char> &diffs,
    int &Dmax, int &Kmax)  {
  Dmax = -1;
  Kmax = -1;

  for(int i = 0; i < 3 && i < diffs.size(); i++) {
    if(diffs[i] > Dmax) {
      Dmax = diffs[i];
      Kmax = i;
    }
  }
}

int gpulp::get_choice_of_case(GravityContextFloat &ctx) {
  int cas = -1;

  if(ctx.Dmax < 8) {
    cas = 7;
  }
  else if(ctx.Kmax == 0) {
    cas = ctx.Nmax[0];
  }
  else if(ctx.Kmax == 2) {
    cas = ctx.Nmax[3];
  }
  else {
    if((ctx.Nmax[0] == 0 && ctx.Nmax[1] == 1) ||
       (ctx.Nmax[0] == 2 && ctx.Nmax[1] == 3)) {
      cas = 5;
    }
    else if((ctx.Nmax[0] == 0 && ctx.Nmax[1] == 2) ||
            (ctx.Nmax[0] == 1 && ctx.Nmax[1] == 3)) {
      cas = 6;
    }
    else {
      cas = 7;
    }
  }

  ctx.cas = cas;

  return cas;
}

std::vector<float> gpulp::get_weights(GravityContextFloat &ctx) {
  std::vector<float> w(4, 0);

  if(ctx.cas == 0) {
    if(ctx.interpolationCtx.dy < (0.5 - ctx.interpolationCtx.dx)) {
      w[0] = 1;
    }
    else {
      w[1] = ctx.dst[2] * ctx.dst[3];
      w[2] = ctx.dst[1] * ctx.dst[3];
      w[3] = ctx.dst[1] * ctx.dst[2];
    }
  }
  else if(ctx.cas == 1) {
    if(ctx.interpolationCtx.dy < 0.5 - ctx.interpolationCtx.dx) {
      w[1] = 1;
    }
    else {
      w[0] = ctx.dst[2]*ctx.dst[3];
      w[2] = ctx.dst[0]*ctx.dst[3];
      w[3] = ctx.dst[0]*ctx.dst[2];
    }
  }
  else if(ctx.cas == 2) {
    if(ctx.interpolationCtx.dy > 0.5 + ctx.interpolationCtx.dx) {
      w[2] = 1;
    }
    else {
      w[0] = ctx.dst[1]*ctx.dst[3];
      w[1] = ctx.dst[0]*ctx.dst[3];
      w[3] = ctx.dst[0]*ctx.dst[1];
    }
  }
  else if(ctx.cas == 3) {
    if(ctx.interpolationCtx.dy > 1.5 - ctx.interpolationCtx.dx) {
      w[3] = 1;
    }
    else {
      w[0] = ctx.dst[1]*ctx.dst[2];
      w[1] = ctx.dst[0]*ctx.dst[2];
      w[2] = ctx.dst[0]*ctx.dst[1];
    }
  }
  else if(ctx.cas == 5) {
    if(ctx.interpolationCtx.dy < 0.5) {
      w[0] = ctx.dst[1];
      w[1] = ctx.dst[0];
    }
    else {
      w[2] = ctx.dst[3];
      w[3] = ctx.dst[2];
    }
  }
  else if(ctx.cas == 6) {
    if(ctx.interpolationCtx.dx < 0.5) {
      w[0] = ctx.dst[2];
      w[2] = ctx.dst[0];
    }
    else {
      w[1] = ctx.dst[3];
      w[3] = ctx.dst[1];
    }
  }
  else {
    w[0] = ctx.dst[1]*ctx.dst[2]*ctx.dst[3];
    w[1] = ctx.dst[0]*ctx.dst[2]*ctx.dst[3];
    w[2] = ctx.dst[0]*ctx.dst[1]*ctx.dst[3];
    w[3] = ctx.dst[0]*ctx.dst[1]*ctx.dst[2];
  }

  return w;
}

std::vector<float> gpulp::normalize_weights(std::vector<float> &w) {
  float sum = 0;
  for(int i = 0; i < 4; i++) {
    sum += w[i];
  }

  for(int i = 0; i < 4; i++) {
    w[i] /= sum;
  }

  return w;
}

GravityContextFloat gpulp::get_gravity_ctx(InterpolationContextFloat &iCtx) {
  GravityContextFloat ctx;

  ctx.interpolationCtx = iCtx;
  ctx.dst = get_gravity_distances(iCtx);
  PixelArr sorted = sort_pixels(iCtx);
  std::vector<unsigned char> diffs = diff_pixels(sorted);
  maximum_jump(diffs, ctx.Dmax, ctx.Kmax);
  ctx.Nmax = arg_sort_pixels(iCtx);
  ctx.cas = get_choice_of_case(ctx);
  ctx.w = get_weights(ctx);
  ctx.w = normalize_weights(ctx.w);

  return ctx;
}

PixelMono gpulp::doInterpolation(InterpolationContextFloat &iCtx) {
  GravityContextFloat ctx = get_gravity_ctx(iCtx);

  unsigned char val;
  val += ctx.w[0]*ctx.interpolationCtx.a->getData()[0];
  val += ctx.w[1]*ctx.interpolationCtx.b->getData()[0];
  val += ctx.w[2]*ctx.interpolationCtx.c->getData()[0];
  val += ctx.w[3]*ctx.interpolationCtx.d->getData()[0];

  return PixelMono(val);
}
