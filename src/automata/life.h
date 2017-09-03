#ifndef LIFE_H
#define LIFE_H

#include "automata/life_like.h"
#include "curses/screen.h"
#include "grid/toroidal_grid.h"

namespace Automata {

class Life : public LifeLike {
public:
    Life(int nsize_x, int nsize_y);
};

};

#endif
