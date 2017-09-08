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

#include "automata/life_like.h"
#include "curses/screen.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << argv[0] << " rulestring" << std::endl;
        return 1;
    }
    Curses::Screen screen;
    try {
        Automata::LifeLike automaton(screen.get_max_x(), screen.get_max_y(), argv[1]);
        const int rate = 100000;
        for (;;) {
            usleep(rate);
            std::cerr << "Generation: " << automaton.get_curr_gen() << " - ";
            std::cerr << "Population: " << automaton.get_population() << std::endl;
            automaton.draw(screen);
            automaton.update();
        }
    } catch (const std::invalid_argument &ex) {
        /* TODO: This does not print to the screen, do it some other way */
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
