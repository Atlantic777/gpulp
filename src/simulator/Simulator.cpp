#include "simulator/Simulator.h"
#include "gpulp/Painter.h"
#include <iostream>

using namespace gpulp;

Simulator::Simulator(std::string algorithm, std::string mathlib) {
  this->algorithm = algorithm;
  this->mathlib = mathlib;

  if(algorithm == "bilinear") {
    p = new PainterBilinearFloat();
  }
  else if(algorithm == "gravity") {
    p = new PainterGravityFloat();
  }
}

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
  p->render(*fb, obj);
}
