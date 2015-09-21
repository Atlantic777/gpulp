#include "simulator/FrameBuffer.h"

using namespace gpulp;

FrameBuffer* FrameBuffer::create(Size size, Channels type) {
  FrameBuffer *fb;

  if(type == ch_mono) {
    fb = new FrameBufferMono(size);
  }
  else {
    fb = NULL;
  }

  return fb;
}

FrameBufferMono::FrameBufferMono(Size size) {
  this->size = size;

  data = new PixelMono*[size.width];
  for(int i = 0; i < size.width; i++) {
    data[i] = new PixelMono[size.height];
  }
}

Pixel& FrameBufferMono::read(int col, int row) {
  return data[col][row];
}

void FrameBufferMono::write(int col, int row, Pixel &p) {
  data[col][row] = p;
}
