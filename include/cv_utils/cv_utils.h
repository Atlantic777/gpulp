#ifndef CV_UTILS_H
#define CV_UTILS_H

#include "simulator/FrameBuffer.h"
#include "opencv2/opencv.hpp"

using namespace gpulp;

cv::Mat FrameBuffer2Mat(FrameBuffer *fb) {
  printf("%d %d\n", fb->size.height, fb->size.width);

  cv::Mat m = cv::Mat::zeros(fb->size.height, fb->size.width, CV_8UC1);

  for(int row = 0; row < fb->size.height; row++) {
    for(int col = 0; col < fb->size.width; col++) {
      m.at<unsigned char>(row, col) = fb->read(row,col).getData()[0];
    }
  }

  return m;
}

#endif
