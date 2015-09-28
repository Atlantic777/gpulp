#include "gpulp/Painter.h"
#include "gpulp/InterpolationContext.h"
#include "gpulp/gravity_utils.h"
#include <iostream>
#include <cmath>

using namespace gpulp;
using namespace std;

void Painter::render(FrameBuffer &fb, GUIObject obj) {
  if(obj.size == obj.texture.size) {
    blit(fb, obj);
  }
  else {
    stretchBlit(fb, obj);
  }
}

void Painter::blit(FrameBuffer &fb, GUIObject obj) {
  int width  = obj.texture.size.width;
  int height = obj.texture.size.height;

  int tx, ty;

  for(int row = 0; row < height; row++) {
    for(int col = 0; col < width; col++) {
      tx = obj.location.x + col;
      ty = obj.location.y + row;

      fb.write(tx, ty, obj.texture.data[col][row]);
    }
  }
}

void Painter::stretchBlit(FrameBuffer &fb, GUIObject obj) {
  for(int col = 0; col < obj.size.width; col++) {
    for(int row = 0; row < obj.size.height; row++) {
      PixelMono p = interpolate(Location(col, row), fb, obj);
      fb.write(col, row, p);
    }
  }
}

InterpolationContextFloat PainterFloat::getInterpolationContext(Location l,
    FrameBuffer &fb, GUIObject &obj) {
  InterpolationContextFloat ctx;

  int w = obj.texture.size.width;
  int h = obj.texture.size.height;

  int w2 = obj.size.width;
  int h2 = obj.size.height;

  float x_ratio = ((float)(w-1))/w2;
  float y_ratio = ((float)(h-1))/h2;

  int x = (int)(x_ratio*l.x);
  int y = (int)(y_ratio*l.y);

  float x_diff = (x_ratio*l.x) - x;
  float y_diff = (y_ratio*l.y) - y;

  int step_x = !(obj.texture.size.width  == 1);
  int step_y = !(obj.texture.size.height == 1);

  Location a(x         , y);
  Location b(x + step_x, y);
  Location c(x         , y + step_y);
  Location d(x + step_x, y + step_y);

  ctx.a = &obj.texture.data[a.x][a.y];
  ctx.b = &obj.texture.data[b.x][b.y];
  ctx.c = &obj.texture.data[c.x][c.y];
  ctx.d = &obj.texture.data[d.x][d.y];

  ctx.dx = x_diff;
  ctx.dy = y_diff;

  return ctx;
}

InterpolationContextFixed PainterFixed::getInterpolationContext(Location l,
    FrameBuffer &fb, GUIObject &obj) {
  InterpolationContextFixed ctx;

  int w = obj.texture.size.width;
  int h = obj.texture.size.height;

  int w2 = obj.size.width;
  int h2 = obj.size.height;

  float fx_ratio = ((float)(w-1))/w2;
  float fy_ratio = ((float)(h-1))/h2;

  FPNum x_ratio = to_fixed(fx_ratio);
  FPNum y_ratio = to_fixed(fy_ratio);

  int x = mul(x_ratio, to_fixed(l.x)) >> L_BITS;
  int y = mul(y_ratio, to_fixed(l.y)) >> L_BITS;

  FPNum x_diff = mul(x_ratio,to_fixed(l.x)) - to_fixed(x);
  FPNum y_diff = mul(y_ratio,to_fixed(l.y)) - to_fixed(y);

  int step_x = !(obj.texture.size.width  == 1);
  int step_y = !(obj.texture.size.height == 1);

  Location a(x         , y);
  Location b(x + step_x, y);
  Location c(x         , y + step_y);
  Location d(x + step_x, y + step_y);

  ctx.a = &obj.texture.data[a.x][a.y];
  ctx.b = &obj.texture.data[b.x][b.y];
  ctx.c = &obj.texture.data[c.x][c.y];
  ctx.d = &obj.texture.data[d.x][d.y];

  ctx.dx = x_diff;
  ctx.dy = y_diff;

  return ctx;
}

PixelMono PainterBilinearFixed::interpolate(Location l, FrameBuffer &fb, GUIObject obj) {
  InterpolationContextFixed ctx = getInterpolationContext(l, fb, obj);

  FPNum a_val = to_fixed(ctx.a->getData()[0]);
  FPNum b_val = to_fixed(ctx.b->getData()[0]);
  FPNum c_val = to_fixed(ctx.c->getData()[0]);
  FPNum d_val = to_fixed(ctx.d->getData()[0]);

  FPNum one = to_fixed(1);

  FPNum fq1;
  FPNum fq2;
  FPNum fp;

  fq1 = mul(a_val, one - ctx.dx) + mul(b_val, ctx.dx);
  fq2 = mul(c_val, one - ctx.dx) + mul(d_val, ctx.dx);
  fp  = mul(fq1, one - ctx.dy) + mul(fq2, ctx.dy);

  PixelMono p(fp >> L_BITS);
  return p;
}

PixelMono PainterBilinearFloat::interpolate(Location l, FrameBuffer &fb, GUIObject obj) {
  InterpolationContextFloat ctx = getInterpolationContext(l, fb, obj);

  PixelMono q1(
    ctx.a->getData()[0]*(1-ctx.dx) +
    ctx.b->getData()[0]*(ctx.dx));

  PixelMono q2(
    ctx.c->getData()[0]*(1-ctx.dx) +
    ctx.d->getData()[0]*(ctx.dx));

  PixelMono p(
      q1.getData()[0]*(1-ctx.dy) +
      q2.getData()[0]*ctx.dy);

  return p;
}

PixelMono PainterGravityFloat::interpolate(Location l, FrameBuffer &fb, GUIObject obj) {
  InterpolationContextFloat iCtx = getInterpolationContext(l, fb, obj);
  GravityContextFloat ctx(iCtx);

  unsigned char val;
  val += ctx.w[0]*ctx.interpolationCtx.a->getData()[0];
  val += ctx.w[1]*ctx.interpolationCtx.b->getData()[0];
  val += ctx.w[2]*ctx.interpolationCtx.c->getData()[0];
  val += ctx.w[3]*ctx.interpolationCtx.d->getData()[0];

  return PixelMono(val);
}
PixelMono PainterGravityFixed::interpolate(Location l, FrameBuffer &fb, GUIObject obj) {
  InterpolationContextFixed iCtx = getInterpolationContext(l, fb, obj);
  GravityContextFixed ctx(iCtx);

  unsigned char val;
  val += mul(ctx.w[0], to_fixed(ctx.interpolationCtx.a->getData()[0]));
  val += mul(ctx.w[1], to_fixed(ctx.interpolationCtx.b->getData()[0]));
  val += mul(ctx.w[2], to_fixed(ctx.interpolationCtx.c->getData()[0]));
  val += mul(ctx.w[3], to_fixed(ctx.interpolationCtx.d->getData()[0]));

  return PixelMono(from_fixed(val));
}
