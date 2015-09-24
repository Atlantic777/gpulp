#include "gpulp/Painter.h"
#include "gpulp/InterpolationContext.h"
#include <iostream>

using namespace gpulp;
using namespace std;

void Painter::render(FrameBuffer &fb, GUIObject obj) {
  if(obj.size == obj.texture.size) {
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
  InterpolationContext ctx;

  for(int col = 0; col < obj.size.width; col++) {
    for(int row = 0; row < obj.size.height; row++) {
      ctx = getInterpolationContext(Location(col, row), fb, obj);

      PixelMono q1(
        ctx.a->getData()[0]*ctx.dx +
        ctx.b->getData()[0]*(1 - ctx.dx));

      PixelMono q2(
        ctx.c->getData()[0]*ctx.dx +
        ctx.d->getData()[0]*(1-ctx.dx));

      PixelMono p(
          q1.getData()[0]*ctx.dy +
          q1.getData()[0]*(1-ctx.dy));

      fb.write(col, row, p);
    }
  }
}

InterpolationContext Painter::getInterpolationContext(Location l,
    FrameBuffer &fb, GUIObject &obj) {
  InterpolationContext ctx;

  int w = obj.texture.size.width;
  int h = obj.texture.size.height;

  int w2 = obj.size.width;
  int h2 = obj.size.height;

  float x_ratio = ((float)(w-1))/w2;
  float y_ratio = ((float)(h-1))/h2;

  int x = (int)(x_ratio*l.x);
  int y = (int)(y_ratio*l.y);

  float x_diff = (x_ratio*l.x) - x;
  float y_diff = (y_ratio*l.y) - y;

  int step_x = !(obj.texture.size.width  == 1);
  int step_y = !(obj.texture.size.height == 1);

  Location a(x, y);
  Location b(x + step_x, y);
  Location c(x         , y + step_y);
  Location d(x + step_x, y + step_y);

  ctx.a = &obj.texture.data[a.x][a.y];
  ctx.b = &obj.texture.data[b.x][b.y];
  ctx.c = &obj.texture.data[c.x][c.y];
  ctx.d = &obj.texture.data[d.x][d.y];

  ctx.dx = x_diff;
  ctx.dy = y_diff;

  return ctx;
}
