#include "gpulp/Painter.h"
#include "gpulp/InterpolationContext.h"
#include <iostream>

using namespace gpulp;
using namespace std;

void Painter::render(FrameBuffer &fb, GUIObject obj) {
  if(obj.scale.fx == 1 && obj.scale.fy == 1) {
    blit(fb, obj);
  }
  else {
    stretchBlit(fb, obj);
  }
}

void Painter::blit(FrameBuffer &fb, GUIObject obj) {
  int width  = obj.texture.size.width;
  int height = obj.texture.size.height;

  int tx, ty;

  for(int row = 0; row < height; row++) {
    for(int col = 0; col < width; col++) {
      tx = obj.location.x + col;
      ty = obj.location.y + row;

      fb.write(tx, ty, obj.texture.data[col][row]);
    }
  }
}

void PainterBilinearFloat::stretchBlit(FrameBuffer &fb, GUIObject obj) {
  int width  = obj.texture.size.width  * obj.scale.fx;
  int height = obj.texture.size.height * obj.scale.fy;

  int sx, sy, dx, dy;
  int tx, ty;

  for(int col = 0; col < width; col++) {
    for(int row = 0; row < height; row++) {
      getInterpolationContext(Location(col, row), fb, obj);
    }
  }
}

InterpolationContext Painter::getInterpolationContext(Location l,
    FrameBuffer &fb, GUIObject &obj) {
  InterpolationContext ctx;

  float fx = obj.scale.fx;
  float fy = obj.scale.fy;

  std::map<char, Location> m = getSourceLocations(l, obj);

  Location &a = m['a'];
  Location &b = m['b'];
  Location &c = m['c'];
  Location &d = m['d'];


  ctx.a = &obj.texture.data[a.x][a.y];
  ctx.b = &obj.texture.data[b.x][b.y];
  ctx.c = &obj.texture.data[c.x][c.y];
  ctx.d = &obj.texture.data[d.x][d.y];

  return ctx;
}

std::map<char, Location> Painter::getSourceLocations(
    Location l, GUIObject obj) {
  std::map<char, Location> m;

  int w = obj.texture.size.width;
  int h = obj.texture.size.height;

  int w2 = obj.texture.size.width  * obj.scale.fx;
  int h2 = obj.texture.size.height * obj.scale.fy;

  float x_ratio = ((float)(w-1))/w2;
  float y_ratio = ((float)(h-1))/h2;

  int x = (int)(x_ratio*l.x);
  int y = (int)(y_ratio*l.y);

  float x_diff = (x_ratio*l.x) - x;
  float y_diff = (y_ratio*l.y) - y;

  int step_x = !(obj.texture.size.width  == 1);
  int step_y = !(obj.texture.size.height == 1);

  m['a'] = Location(x, y);
  m['b'] = Location(x + step_x, y);
  m['c'] = Location(x         , y + step_y);
  m['d'] = Location(x + step_x, y + step_y);

  return m;
}
