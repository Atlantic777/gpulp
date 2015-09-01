#include "gtest/gtest.h"
#include "gpulp/Scene.h"
#include "gpulp/CmdGenerator.h"
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

TEST(CmdParser, ParseEmptyScene) {
}
