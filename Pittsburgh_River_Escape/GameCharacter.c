#include <gb/gb.h>

//generical character structure; id, position, graphics

struct GameCharacter {
    UBYTE spriteids[4]; // all chracters use 4 sprites
    UINT8 x;
    UINT8 y;
    UINT8 width;
    UINT8 height;


};