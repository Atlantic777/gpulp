#ifndef GPULP_UTILS_H
#define GPULP_UTILS_H

#include <string>

namespace gpulp {

class Pixel;
class PixelMono;

struct Location{
    int x;
    int y;

    Location(int x, int y) { this->x = x; this->y = y; }
    Location() {
      x = -1;
      y = -1;
    }
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

    bool operator==(const Size &other) const {
      return (this->width == other.width) && (this->height == other.height);
    }
};

class TextureMono {
  public:
    Size size;
    std::string path;
    int location;
    int id;
    PixelMono **data;

    TextureMono(std::string p, Size s) : path(p), size(s) {}
    TextureMono() {}

    void setId(int id);

    static TextureMono fromColor(std::string color, Size s);
};

class Pixel {
  public:
    virtual unsigned char* getData() const = 0;
    virtual void  setData(unsigned char *data) = 0;
    unsigned char *data;
};

class PixelMono : public Pixel {
  public:
    PixelMono() {
      data = new unsigned char;
      data[0] = 0;
    }

    PixelMono(unsigned char val) {
      data = new unsigned char;
      data[0] = val;
    }

    unsigned char* getData() const { return data; }
    void setData(unsigned char *data) { this->data[0] = data[0]; }

    PixelMono& operator=(const PixelMono &other) {
      this->data[0] = other.getData()[0];
      return *this;
    }

    PixelMono& operator=(const Pixel &other) {
      this->data[0] = other.getData()[0];
      return *this;
    }


  // private:
    // unsigned char *data;
};

enum Channels {ch_mono = 1, ch_color = 3};

}

#endif
