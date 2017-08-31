#ifndef LIFE_H
#define LIFE_H

#include "curses/screen.h"
#include "grid/toroidal_grid.h"

namespace Automata {

class Life {
public:
    Life(int size_x_, int size_y_);

    void update();
    void draw(Curses::Screen &screen) const;

    unsigned long get_curr_gen() const;
private:
    struct Cell {
        enum State { ALIVE, DEAD };

        explicit Cell(State state_ = DEAD);

        const Curses::Color &color() const;
        char symbol() const;

        State state;
    };

    const int size_x;
    const int size_y;
    Grid::ToroidalGrid<Cell> grid;
    unsigned long curr_gen;
};

};

#endif
