#include <cstdint>
#include <iostream>

using namespace std;

// macros
#define DEBUG(var) do{ cout << #var << " = " << var << endl; }while(0)

// types
typedef unsigned int uint;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

struct Pixel {
	u8 red;
	u8 green;
	u8 blue;

	Pixel()
		: red(0), green(0), blue(0) {
	}
	Pixel(u8 same_for_all)
		: red(same_for_all), green(same_for_all), blue(same_for_all) {
	}
};

struct Rect{
	u16 y;
	u16 x;
	u16 h;
	u16 w;

	Rect(u16 y_, u16 x_, u16 h_, u16 w_)
		: y(y_), x(x_), h(h_), w(w_) {
	}
};

struct Surface {
	Rect rect;
	Pixel* mem;
	u16 mem_width;

	Surface(const Rect& rect_, Pixel* mem_, u16 mem_width_)
		: rect(rect_), mem(mem_), mem_width(mem_width_) {
	}
};

// functions
bool operator==(const Pixel& x, const Pixel& y) {
	return x.red == y.red && x.green == y.green && x.blue == y.blue;
}

ostream& operator<<(ostream& os, const Pixel& p) {
	return os << "Pixel(" << u32(p.red) << ", " << u32(p.green) << ", " << u32(p.blue) << ")";
}

int main()
{
    return 0;
}
