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

#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>

int main()
{
    Automata::Life automaton(1000, 1000);
    for (;;) {
        automaton.update();
        std::cout << "gen: " << automaton.get_curr_gen() << ", pop: " <<
            automaton.get_population() << '\n';
    }
    return 0;
}
