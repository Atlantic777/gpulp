#include "gpulp/Painter.h"

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
