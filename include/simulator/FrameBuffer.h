#ifndef GPULP_FRAMEBUFFER_H
#define GPULP_FRAMEBUFFER_H

#include "gpulp/gpulp_utils.h"

namespace gpulp {

class FrameBuffer {
  public:
    Size size;
    virtual Pixel& read(int row, int col) = 0;
    virtual void  write(int row, int col, Pixel &p) = 0;

    static FrameBuffer* create(Size size, Channels type);
};

class FrameBufferMono : public FrameBuffer {
  public:
    FrameBufferMono(Size size);
    Pixel& read(int col, int row);
    void   write(int col, int row, Pixel &p);

  private:
    PixelMono **data;
};


}

#endif
