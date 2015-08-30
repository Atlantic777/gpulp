#ifndef GPULP_COMMAND_H
#define GPULP_COMMAND_H

namespace gpulp {

enum BlitType {Blit, StretchBlit};
enum CullType {Over, Alpha};

struct Command {
    BlitType blit;
    CullType cull;

    unsigned long location;
    Size  size;
    Scale scale;
};
}

#endif
