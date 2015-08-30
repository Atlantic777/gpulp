#ifndef GPULP_UTILS_H
#define GPULP_UTILS_H

#include <string>

namespace gpulp {
struct Location{
    int x;
    int y;

    Location(int x, int y) { this->x = x; this->y = y; }
    Location() {}
};

struct Scale {
    float fx;
    float fy;

    Scale(float fx, float fy) { this->fx = fx; this->fy = fy; }
    Scale() {}
};

struct Size {
    int width;
    int height;

    Size(int w, int h) {width = w; height = h;}
    Size() {}
};

struct Texture {
    std::string path;
    Size size;

    Texture(std::string p, Size s) : path(p), size(s) {}
    Texture() {}
};

struct Pixel {
    int r;
    int g;
    int b;
};

enum Channels {ch_mono = 1, ch_color = 3};

}

#endif
