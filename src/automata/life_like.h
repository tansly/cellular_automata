#ifndef LIFE_LIKE_H
#define LIFE_LIKE_H

#include "curses/screen.h"
#include "grid/toroidal_grid.h"

#include <string>

namespace Automata {

class LifeLike {
public:
    LifeLike(int nsize_x, int nsize_y, const std::string &rule);

    void update();
    void draw(Curses::Screen &screen) const;

    unsigned long get_curr_gen() const;
private:
    struct Cell {
        enum State { ALIVE, DEAD };

        explicit Cell(State nstate = DEAD);

        const Curses::Color &color() const;
        char symbol() const;

        State state;
    };

    int size_x;
    int size_y;
    std::string rule_born;
    std::string rule_survive;
    Grid::ToroidalGrid<Cell> grid;
    unsigned long curr_gen;
};

};

#endif
