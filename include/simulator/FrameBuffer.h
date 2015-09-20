#ifndef GPULP_FRAMEBUFFER_H
#define GPULP_FRAMEBUFFER_H

#include "gpulp/gpulp_utils.h"

namespace gpulp {

class FrameBuffer {
  public:
    virtual Pixel& read(int row, int col) = 0;
    virtual void  write(int row, int col, Pixel &p) = 0;

    static FrameBuffer* create(Size size, Channels type);
};

class FrameBufferMono : public FrameBuffer {
  public:
    FrameBufferMono(Size size);
    Pixel& read(int row, int col);
    void   write(int row, int col, Pixel &p);

  private:
    PixelMono **data;
};


}

#endif
