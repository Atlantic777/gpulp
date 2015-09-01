#include "gtest/gtest.h"
#include "gpulp/Scene.h"
#include "opencv2/opencv.hpp"
#include "gpulp/gpulp_utils.h"
#include "simulator/Simulator.h"

using namespace gpulp;

TEST(Simulator, RenderEmptyScene) {
  int width  = 3;
  int height = 3;

  Scene scene(Size(width, height), ch_mono);

  Simulator sim;
  sim.setScene(&scene);

  cv::Mat m = sim.render();

  for(int i = 0; i < width; i++) {
    for(int j = 0; j < height; j++) {
      EXPECT_EQ(0, m.at<unsigned char>(i, j));
    }
  }
}

TEST(Simulator, FileParser) {
  FAIL() << "Finish the test!";
}

TEST(Simulator, LoadResources) {
  FAIL() << "Finish the test!";
}

TEST(Simulator, CmdParser) {
  FAIL() << "Finish the test";
}

TEST(Simulator, RenderOneObject) {
  FAIL() << "Finish the test!";
}
