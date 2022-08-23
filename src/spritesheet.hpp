#ifndef SPRITESHEET_HPP_INCLUDE
#define SPRITESHEET_HPP_INCLUDE

#include "RSDL/rsdl.hpp"

namespace sprite {

extern const char GAMETILES_FILE[];
extern const char BUTTON_FILE[];
extern const char DOODLE_FILE[];

struct Tile {
    Tile();
    Tile(int x_, int y_, int w_, int h_);
    Tile(const Rectangle& xywh);

    int x, y, w, h;

    operator Rectangle() const {
        return Rectangle(x, y, w, h);
    }
};

enum Doodle {
    LEFT,
    RIGHT,
    LEFTJUMP,
    RIGHTJUMP,
};

enum Button {
    PLAY,
    QUIT,
    RESUME,
    MENU,
    PLAYAGAIN,
};

enum Platform {
    NORMAL,
    MOVABLE,

    BREAKABLE,
    BREAKABLE_B1,
    BREAKABLE_B2,
    BREAKABLE_B3,
};

enum Item {
    SPRING,
    SPRUNG,
};

enum Enemy {
    NORM,

    UFO_OFF,
    UFO_ON,
};

extern const Tile doodle[4];
extern const Tile button[5];

extern const Tile platform[6];
extern const Tile item[2];
extern const Tile enemy[3];

} // namespace sprite

#endif // SPRITESHEET_HPP_INCLUDE
