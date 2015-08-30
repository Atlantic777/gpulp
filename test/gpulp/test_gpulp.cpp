#include "gtest/gtest.h"
#include "gpulp/Scene.h"
#include "gpulp/CmdGenerator.h"
#include "gpulp/gpulp_utils.h"

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
    FAIL() << "finish the test";
}
