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

#include "automata/predator_and_prey.h"
#include "curses/screen.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>

int main(int argc, char **argv)
{
    Curses::Screen screen;
    Automata::PredatorAndPrey automaton(screen.get_max_x(), screen.get_max_y());
    const int max_gen = 10000;
    int rate = 100000;
    if (argc == 2) {
        try {
            rate = std::stoi(std::string(argv[1]));
        } catch (const std::invalid_argument &ex) {
            std::cerr << "Invalid argument" << std::endl;
            return 1;
        }
    }
    while (automaton.get_curr_gen() < max_gen) {
        usleep(rate);
        automaton.draw(screen);
        automaton.update();
    }
    return 0;
}
