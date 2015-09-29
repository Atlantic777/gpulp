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
    void render(FrameBuffer &fb, const GUIObject &obj);
    void blit(FrameBuffer &fb, const GUIObject &obj);
    void stretchBlit(FrameBuffer &fb, const GUIObject &obj);

  private:
    virtual PixelMono interpolate(Location l, const FrameBuffer &fb, const GUIObject &obj) = 0;
};

class PainterFixed {
  public:
    InterpolationContextFixed getInterpolationContext(Location l,
        const FrameBuffer &fb, const GUIObject &obj);
};

class PainterFloat {
  public:
    InterpolationContextFloat getInterpolationContext(Location l,
        const FrameBuffer &fb, const GUIObject &obj);
};

class PainterBilinearFloat : public Painter, public PainterFloat {
  private:
    PixelMono interpolate(Location l, const FrameBuffer &fb, const GUIObject &obj);
};

class PainterBilinearFixed : public Painter, public PainterFixed {
  private:
    PixelMono interpolate(Location l, const FrameBuffer &fb, const GUIObject &obj);
};

class PainterGravityFloat : public Painter, public PainterFloat {
  private:
    PixelMono interpolate(Location l, const FrameBuffer &fb, const GUIObject &obj);
};

class PainterGravityFixed : public Painter, public PainterFixed {
  private:
    PixelMono interpolate(Location l, const FrameBuffer &fb, const GUIObject &obj);
};

}

#endif
