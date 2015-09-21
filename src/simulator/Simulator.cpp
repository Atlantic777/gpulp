#include "simulator/Simulator.h"
#include <iostream>

using namespace gpulp;

void Simulator::setScene(Scene *s) {
  scene = s;
  fb = FrameBuffer::create(scene->size, scene->channels);
}

FrameBuffer* Simulator::render() {
  for(auto obj : scene->objects) {
    renderOne(obj);
  }

  return fb;
}

void Simulator::renderOne(GUIObject obj) {
  int width = obj.texture.size.width;
  int height = obj.texture.size.height;

  int px = obj.location.x;
  int py = obj.location.y;

  for(int col = 0; col < width; col++) {
    for(int row = 0; row < height; row++) {
      int ty = py + row;
      int tx = px + col;

      fb->write(tx, ty, obj.texture.data[col][row]);
    }
  }
}
