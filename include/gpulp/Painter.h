#ifndef GPULP_PAINTER_H
#define GPULP_PAINTER_H

class Painter {
  public:
    virtual void renderObject();
  private:
    virtual void blit();
    virtual void stretchBlit();
};

class PainterBilinarFloat : public Painter {
  public:
    virtual void renderObject();
  private:
    void blit() {}
    void stretchBlit() {}
};

class PainterBilinearFixed : public Painter {
  public:
    virtual void renderObject();
  private:
    void blit() {}
    void stretchBlit() {}
};

class PainterGravityFloat : public Painter {
  public:
    virtual void renderObject();
  private:
    void blit() {}
    void stretchBlit() {}
};

class PainterGravityFixed : public Painter {
  public:
    virtual void renderObject();
  private:
    void blit() {}
    void stretchBlit() {}
};

#endif
