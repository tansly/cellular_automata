#include "automata/life.h"
#include "curses/screen.h"
#include "grid/toroidal_grid.h"

#include <algorithm>
#include <random>

namespace Automata {

Life::Life(int nsize_x, int nsize_y) :
    LifeLike(nsize_x, nsize_y, "B3/S23")
{
}

};
