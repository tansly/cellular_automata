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

#ifndef PREDATOR_AND_PREY_H
#define PREDATOR_AND_PREY_H

#include "curses/screen.h"
#include "grid/toroidal_grid.h"

#include <random>

namespace Automata {

class PredatorAndPrey {
public:
    explicit PredatorAndPrey(int size_x_, int size_y_, double prey_dr = 0.85,
            double predator_dr = 0.85);
    void update();
    void run(int gens);
    void draw(Curses::Screen &screen);

    unsigned long get_curr_gen() const;
private:
    struct Creature {
        enum CreatureType { PREDATOR, PREY, EMPTY };

        explicit Creature(CreatureType type_ = Creature::EMPTY);

        const Curses::Color &color() const;
        char symbol() const;

        CreatureType type;
    };

    bool out_of_field(int x, int y) const;

    const int size_x;
    const int size_y;
    Grid::ToroidalGrid<Creature> field;
    unsigned long curr_gen;
    std::mt19937 rng;
    std::bernoulli_distribution prey_disperse;
    std::bernoulli_distribution predator_disperse;
};

};

#endif
