#include <cstdint>
#include <iostream>
#include "gpulp_utils.h"
#include "Scene.h"
#include <string>
#include "GUIObject.h"
#include "CmdGenerator.h"

using namespace std;
using namespace gpulp;

int main()
{
  Scene s(Size(640, 480), mono);

  GUIObject o;
  o.location = Location(100, 100);
  o.scale = Scale(1, 1);
  o.texture = Texture("/tmp/image.png", Size(200, 300));
  o.alpha = 1;

  s.addObject(o);

  CmdGenerator gen;
  gen.setScene(&s);
  string commands = gen.generate();

  cout << commands << endl;

  return 0;
}
