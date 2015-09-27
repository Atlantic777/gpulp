#ifndef GPULP_PAINTER_H
#define GPULP_PAINTER_H

#include "simulator/FrameBuffer.h"
#include "gpulp/GUIObject.h"
#include "gpulp/InterpolationContext.h"
#include "gpulp/fixed_point.h"
#include <map>

namespace gpulp {

class Painter {
  public:
    void render(FrameBuffer &fb, GUIObject obj);
    void blit(FrameBuffer &fb, GUIObject obj);
    void stretchBlit(FrameBuffer &fb, GUIObject obj);

  private:
    virtual PixelMono interpolate(Location l, FrameBuffer &fb, GUIObject obj) = 0;
};

class PainterFixed {
  public:
    InterpolationContextFixed getInterpolationContext(Location l,
        FrameBuffer &fb, GUIObject &obj);
};

class PainterFloat {
  public:
    InterpolationContextFloat getInterpolationContext(Location l,
        FrameBuffer &fb, GUIObject &obj);
};

class PainterBilinearFloat : public Painter, public PainterFloat {
  private:
    PixelMono interpolate(Location l, FrameBuffer &fb, GUIObject obj);
};

class PainterBilinearFixed : public Painter, public PainterFixed {
  private:
    PixelMono interpolate(Location l, FrameBuffer &fb, GUIObject obj);
};

class PainterGravityFloat : public Painter, public PainterFloat {
  private:
    PixelMono interpolate(Location l, FrameBuffer &fb, GUIObject obj);
};

class PainterGravityFixed : public Painter, public PainterFixed {
  private:
    PixelMono interpolate(Location l, FrameBuffer &fb, GUIObject obj);
};

}

#endif
