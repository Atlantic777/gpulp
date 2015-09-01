#include "simulator/Simulator.h"
#include <iostream>

using namespace gpulp;

cv::Mat Simulator::render() {
  cv::Mat fb = cv::Mat::zeros(scene->size.width, scene->size.height, CV_8UC1);
  return fb;
}
