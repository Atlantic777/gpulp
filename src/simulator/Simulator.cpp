#include "simulator/Simulator.h"
#include "gpulp/Painter.h"
#include <iostream>

using namespace gpulp;

Simulator::Simulator(std::string algorithm, std::string mathlib) {
  this->algorithm = algorithm;
  this->mathlib = mathlib;

  if(algorithm == "bilinear" && mathlib == "float") {
    p = new PainterBilinearFloat();
  }
  else if(algorithm == "gravity" && mathlib == "float") {
    p = new PainterGravityFloat();
  }
  else if(algorithm == "bilinear" && mathlib == "fixed") {
    p = new PainterBilinearFixed();
  }
  else if(algorithm == "gravity" && mathlib == "fixed") {
    p = new PainterGravityFixed();
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
