#include "gpulp/Painter.h"
#include "gpulp/InterpolationContext.h"

using namespace gpulp;

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

  for(int row = 0; row < height; row++) {
    for(int col = 0; col < width; col++) {
      // TODO: implement this
    }
  }
}

InterpolationContext Painter::getInterpolationContext(Location l,
    FrameBuffer &fb, GUIObject &obj) {
  InterpolationContext ctx;

  ctx.a = &obj.texture.data[0][0];
  ctx.b = &obj.texture.data[0][0];
  ctx.c = &obj.texture.data[0][0];
  ctx.d = &obj.texture.data[0][0];

  return ctx;
}
