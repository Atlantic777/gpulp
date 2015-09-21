#ifndef GPULP_PAINTER_H
#define GPULP_PAINTER_H

#include "simulator/FrameBuffer.h"
#include "gpulp/GUIObject.h"

namespace gpulp {

class Painter {
  public:
    void render(FrameBuffer &fb, GUIObject obj);
  private:
    void blit(FrameBuffer &fb, GUIObject obj);
    virtual void stretchBlit(FrameBuffer &fb, GUIObject obj) = 0;
};

class PainterBilinearFloat : public Painter {
  private:
    void stretchBlit(FrameBuffer &fb, GUIObject obj);
};

class PainterBilinearFixed : public Painter {
  private:
    void stretchBlit() {}
};

class PainterGravityFloat : public Painter {
  private:
    void stretchBlit() {}
};

class PainterGravityFixed : public Painter {
  private:
    void stretchBlit() {}
};

}

#endif
