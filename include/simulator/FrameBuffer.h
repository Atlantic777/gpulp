#ifndef GPULP_FRAMEBUFFER_H
#define GPULP_FRAMEBUFFER_H

namespace gpulp {

class FrameBuffer3 {
    public:
        int read(int location);
        void write(int location, int value);
};
}

#endif
