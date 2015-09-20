#include "gpulp/gpulp_utils.h"
#include <cstdio>

using namespace gpulp;

TextureMono TextureMono::fromColor(std::string color, Size s) {
  TextureMono t;
  t.size = s;

  t.data = new PixelMono*[s.height];
  for(int i = 0; i < s.height; i++) {
    t.data[i] = new PixelMono[s.width];
  }

  PixelMono example;
  unsigned char *colorVal = new unsigned char[0];

  if(color == "white")
    colorVal[0] = 255;
  else
    colorVal[0] = 0;

  example.setData(colorVal);

  for(int row = 0; row < t.size.height; row++) {
    for(int col = 0; col < t.size.width; col++) {
      t.data[row][col] = example;
    }
  }


  return t;
}

void TextureMono::setId(int id) {
  this->id = id;
}
