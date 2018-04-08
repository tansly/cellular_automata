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

#include "automata/life.h"
#include "curses/screen.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>

int main(void)
{
    Curses::Screen screen;
    Automata::Life automaton(screen.get_max_x(), screen.get_max_y());

    for (;;) {
        automaton.draw(screen);
        for (int i = 0; i < 101; ++i) {
            automaton.update();
        }
    }

    return 0;
}
