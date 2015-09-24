#include "simulator/Simulator.h"
#include "gpulp/Painter.h"
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
  PainterBilinearFloat p;
  p.render(*fb, obj);
}
