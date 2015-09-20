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
  data = new PixelMono*[size.height];
  for(int i = 0; i < size.height; i++) {
    data[i] = new PixelMono[size.width];
  }
}

Pixel& FrameBufferMono::read(int row, int col) {
  return data[row][col];
}

void FrameBufferMono::write(int row, int col, Pixel &p) {
  data[row][col] = p;
}
