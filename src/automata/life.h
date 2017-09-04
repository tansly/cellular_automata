/*
    Cellular automaton visualization in C++, using ncurses
    Copyright (C) 2017 Yağmur Oymak

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
