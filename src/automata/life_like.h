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

#ifndef LIFE_LIKE_H
#define LIFE_LIKE_H

#include "curses/screen.h"
#include "grid/toroidal_grid.h"

#include <string>
#include <vector>

namespace Automata {

class LifeLike {
public:
    struct Cell {
        enum State { ALIVE, DEAD };

        explicit Cell(State nstate = DEAD);

        const Curses::Color &color() const;
        char symbol() const;

        void toggle_state();
        State state;
    };

    LifeLike(int size_x, int size_y, const std::string &rule);
    LifeLike(Grid::ToroidalGrid<Cell> ngrid, const std::string &rule);

    void update();
    void draw(Curses::Screen &screen) const;

    unsigned long get_curr_gen() const;
private:
    void init_rules(const std::string &rule);
    void init_rnd_grid();

    std::vector<bool> rule_born;
    std::vector<bool> rule_survive;
    Grid::ToroidalGrid<Cell> grid;
    unsigned long curr_gen;
};

};

#endif
