#include "gtest/gtest.h"
#include "gpulp/Scene.h"
#include "opencv2/opencv.hpp"
#include "gpulp/gpulp_utils.h"
#include "simulator/Simulator.h"
#include "simulator/MemoryManager.h"

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

TEST(Memorymanager, LoadTexture) {
  MemoryManager mem;

  Texture t0 = Texture::fromColor("white", Size(3, 3));
  int id0 = 0;
  t0.setId(id0);

  Texture t1 = Texture::fromColor("white", Size(5, 5));
  int id1 = 1;
  t1.setId(id1);

  mem.addTexture(t0);
  mem.addTexture(t1);

  Texture r0 = mem.getTexture(id0);
  Texture r1 = mem.getTexture(id1);

  ASSERT_EQ(r0.id, t0.id);
  ASSERT_EQ(r1.id, t1.id);
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
}

TEST(Simulator, BlitTwoObjects) {
  int width = 10;
  int height = 15;
  Scene scene(Size(width, height), ch_mono);

  Texture t = Texture::fromColor("white", Size(10, 5));

  GUIObject top, bottom;

  top.texture = t;
  bottom.texture = t;

  top.location = Location(0, 0);
  bottom.location = Location(0, 10);

  scene.addObject(top);
  scene.addObject(bottom);

  Simulator sim;
  sim.setScene(&scene);

  cv::Mat m = sim.render();

  for(int col = 0; col < width; col++) {
    for(int row = 0; row < height; row++) {
      if(row < 5 || row >= 10)
        ASSERT_EQ(255, m.at<unsigned char>(col, row));
      else
        ASSERT_EQ(0, m.at<unsigned char>(col, row));
    }
  }
}

TEST(Simulator, StretchBlitOneObject) {
  FAIL() << "Finish the test!";
}
