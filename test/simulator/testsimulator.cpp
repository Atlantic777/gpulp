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

TEST(Simulator, LoadResources) {
  FAIL() << "Finish the test!";
}

TEST(Simulator, RenderOneObject) {
  FAIL() << "Finish the test!";
}

TEST(Simulator, BlitOneObject) {
  int width  = 10;
  int height = 10;
  Scene scene(Size(width, height), ch_mono);

  Texture plainSquare = Texture::fromColor("white", Size(5, 5));

  GUIObject obj;
  obj.parent = NULL;
  obj.location = Location(0, 0);
  obj.scale = Scale(1, 1);
  obj.texture = plainSquare;
  
  scene.addObject(obj);

  Simulator sim;
  sim.setScene(&scene);

  cv::Mat m = sim.render();

  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      ASSERT_EQ(255, m.at<unsigned char>(i, j));
    }
  }

  FAIL() << "Finish the test!";
}

TEST(Simulator, StretchBlitOneObject) {
  FAIL() << "Finish the test!";
}

TEST(Simulator, BlitTwoObjects) {
  FAIL() << "Finish the test!";
}
