#include "gpulp/gravity_utils.h"
#include <deque>
#include <cmath>

using namespace gpulp;
typedef std::pair<Pixel*, int> PixelPair;
typedef std::deque<PixelPair> PixelPairArr;

PixelPairArr pixel_pair_sort(InterpolationContext &ctx){
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

std::vector<Pixel*> gpulp::sort_pixels(InterpolationContext &ctx) {
  std::vector<Pixel*> parr;
  PixelPairArr pairs = pixel_pair_sort(ctx);

  for(int i = 0; i < 4 && i < pairs.size(); i++) {
    parr.push_back(pairs[i].first);
  }

  return parr;
}

std::vector<int> gpulp::arg_sort_pixels(InterpolationContext &ctx) {
  std::vector<int> args;
  PixelPairArr pairs = pixel_pair_sort(ctx);

  for(int i = 0; i < 4 && i < pairs.size(); i++) {
    args.push_back(pairs[i].second);
  }

  return args;
}

std::vector<float> gpulp::get_gravity_distances(InterpolationContext &ctx) {
  std::vector<float> dst;

  dst.push_back(pow(ctx.dx, 2) + pow(ctx.dy, 2));
  dst.push_back(pow(1-ctx.dx, 2) + pow(ctx.dy, 2));
  dst.push_back(pow(ctx.dx, 2) + pow(1-ctx.dy, 2));
  dst.push_back(pow(1-ctx.dx, 2) + pow(1-ctx.dy, 2));

  return dst;
}
