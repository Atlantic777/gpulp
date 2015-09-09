#include "gtest/gtest.h"
#include "gpulp/Scene.h"
#include "gpulp/CmdGenerator.h"
#include "gpulp/CmdReader.h"
#include "gpulp/gpulp_utils.h"
#include "gpulp/GUIObject.h"
#include <sstream>

using namespace gpulp;

TEST(CmdGenerator, GenerateEmptyScene) {
  CmdGenerator generator;
  Size  scene_size(640, 480);
  Scene scene(scene_size, ch_mono);

  generator.setScene(&scene);
  std::string res = generator.generate();

  std::string target("# WORLD\n640 480 1\n# RESOURCES\n# CMDS\n");
  ASSERT_STREQ(target.c_str(), res.c_str());
}

TEST(CmdGenerator, GenerateOneObject) {
  CmdGenerator generator;
  Scene scene(Size(640, 480), ch_mono);

  GUIObject obj;
  Texture   t("none", Size(200, 300));

  obj.parent     = NULL;
  obj.location.x = 100;
  obj.location.y = 100;
  obj.texture    = t;
  obj.scale      = Scale(1, 1);
  obj.culling    = 0;
  obj.alpha      = 1;

  scene.addObject(obj);

  generator.setScene(&scene);
  std::string res = generator.generate();

  std::stringstream target;
  target << "# WORLD\n"
         << "640 480 1\n"
         << "# RESOURCES\n"
         << "0x0000 none 200 300\n"
         << "# CMDS\n"
         << "100 100 0x0000 200 300 255 255 0 255\n";

  ASSERT_STREQ(target.str().c_str(), res.c_str());
}

TEST(CmdGenerator, CollectResources) {
  CmdGenerator gen;
  Scene scene(Size(640, 480), ch_mono);

  GUIObject obj;
  Texture t("none", Size(200, 300));

  scene.addObject(obj);
  gen.setScene(&scene);

  std::map<std::string, Texture> resources = gen.getResources();

  ASSERT_EQ(1, resources.size());
}

TEST(CmdReader, ReadEmptyScene) {
  std::stringstream example;

  example << "# WORLD\n"
          << "640 480 1\n"
          << "# RESOURCES\n"
          << "# CMDS\n";

  CmdReader reader(example.str());
  Scene scene = reader.read();

  EXPECT_EQ(640, scene.size.width);
  EXPECT_EQ(480, scene.size.height);
  EXPECT_EQ(ch_mono, scene.channels);
  EXPECT_EQ(0, scene.objects.size());
}

TEST(CmdReader, ReadOneResource) {
  std::stringstream example;

  example << "# WORLD\n"
          << "640 480 1\n"
          << "# RESOURCES\n"
          << "0x0000 none 200 300\n"
          << "# CMDS\n";

  CmdReader reader(example.str());
  Scene scene = reader.read();

  EXPECT_EQ(1, scene.resources.size());
  EXPECT_EQ(0x00, scene.resources["none"].location);
}

TEST(Texture, CreateFromColor) {
  Texture t = Texture::fromColor("white", Size(5, 5));

  ASSERT_EQ(5, t.size.width);
  ASSERT_EQ(5, t.size.height);

  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      ASSERT_EQ(255, t.data.at<unsigned char>(i, j));
    }
  }

}
