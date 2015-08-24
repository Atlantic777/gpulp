#ifndef GPULP_UTILS_H
#define GPULP_UTILS_H

namespace gpulp {
struct Location{
    int x;
    int y;
};

struct Scale {
    float fx;
    float fy;
};

struct Size {
    int width;
    int height;
};

struct Texture {
    std::string path;
    Size size;
};

struct Pixel {
    int r;
    int g;
    int b;
};

}

#endif
