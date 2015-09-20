#ifndef CV_UTILS_H
#define CV_UTILS_H

#include "simulator/FrameBuffer.h"
#include "opencv2/opencv.hpp"
#include "gpulp/gpulp_utils.h"

using namespace gpulp;

cv::Mat FrameBuffer2Mat(FrameBuffer *fb) {
  cv::Mat m = cv::Mat::zeros(fb->size.height, fb->size.width, CV_8UC1);

  for(int row = 0; row < fb->size.height; row++) {
    for(int col = 0; col < fb->size.width; col++) {
      m.at<unsigned char>(row, col) = fb->read(row,col).getData()[0];
    }
  }

  return m;
}

TextureMono LoadTexture(std::string path) {
  cv::Mat m = cv::imread(path, CV_LOAD_IMAGE_GRAYSCALE);

  TextureMono t;
  t.size = Size(m.rows, m.cols);

  t.data = new PixelMono*[m.rows];
  for(int i = 0; i < m.rows; i++) {
    t.data[i] = new PixelMono[m.cols];
  }


  for(int row = 0; row < m.rows; row++) {
    for(int col = 0; col < m.cols; col++) {
      t.data[row][col] = PixelMono(m.at<unsigned char>(row, col));
    }
  }

  return t;
}

#endif
