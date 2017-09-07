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
#include "game/game.h"

#include <iostream>
#include <ncurses.h>
#include <unistd.h>

int main()
{
    Curses::Screen screen;
    Grid::ToroidalGrid<Automata::LifeLike::Cell> grid(screen.get_max_x(),
            screen.get_max_y());
    screen.read_grid(grid);
    Automata::LifeLike automaton(std::move(grid), "B3/S23");
    nodelay(stdscr, true);
    bool stepping = false;
    int ch;
    for (;;) {
        usleep(100000);
        automaton.update();
        automaton.draw(screen);
        ch = getch();
        if (ch == 'p') {
            stepping = !stepping;
            nodelay(stdscr, stepping);
        }
    }
    return 0;
}
