#include "simulator/Simulator.h"
#include <iostream>

using namespace gpulp;

void Simulator::setScene(Scene *s) {
  scene = s;
  fb = cv::Mat::zeros(scene->size.width, scene->size.height, CV_8UC1);
}

cv::Mat Simulator::render() {
  for(auto obj : scene->objects) {
    renderOne(obj);
  }
  return fb;
}

void Simulator::renderOne(GUIObject obj) {
  int width = obj.texture.size.width;
  int height = obj.texture.size.height;

  int px = obj.location.x;
  int py = obj.location.y;

  for(int col = 0; col < width; col++) {
    for(int row = 0; row < height; row++) {
      int tx = px + col;
      int ty = py + row;

      unsigned char val = obj.texture.data.at<unsigned char>(col, row);
      fb.at<unsigned char>(tx, ty) = val;
    }
  }
}
