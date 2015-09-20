#include "gpulp/gpulp_utils.h"

using namespace gpulp;

Texture Texture::fromColor(std::string color, Size s) {
  Texture t;
  t.size = s;

  t.data = cv::Mat::zeros(t.size.width, t.size.height, CV_8UC1);

  if(color == "white"){
    for(int i = 0; i < t.size.width; i++) {
      for(int j = 0; j < t.size.height; j++) {
        t.data.at<unsigned char>(i, j) = 255;
      }
    }
  }

  return t;
}

void Texture::setId(int id) {
  this->id = id;
}
