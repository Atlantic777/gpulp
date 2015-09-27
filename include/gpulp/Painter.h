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
    InterpolationContextFloat getInterpolationContext(Location l,
        FrameBuffer &fb, GUIObject &obj);
  private:
    void blit(FrameBuffer &fb, GUIObject obj);
    virtual void stretchBlit(FrameBuffer &fb, GUIObject obj) = 0;
};

class PainterBilinearFloat : public Painter {
  private:
    void stretchBlit(FrameBuffer &fb, GUIObject obj);
};

class PainterBilinearFixed : public Painter {
  public:
    InterpolationContextFixed getInterpolationContext(Location l,
        FrameBuffer &fb, GUIObject &obj);
  private:
    void stretchBlit(FrameBuffer &fb, GUIObject obj);
};

class PainterGravityFloat : public Painter {
  private:
    void stretchBlit(FrameBuffer &fb, GUIObject obj);
    PixelMono interpolate(InterpolationContextFloat &ctx);
};

class PainterGravityFixed : public Painter {
  public:
    InterpolationContextFixed getInterpolationContext(Location l,
        FrameBuffer &fb, GUIObject &obj);
  private:
    void stretchBlit(FrameBuffer &fb, GUIObject obj);
    PixelMono interpolate(InterpolationContextFixed &ctx);
};

}

#endif
