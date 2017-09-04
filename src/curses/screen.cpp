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

#include "curses/screen.h"

#include <ncurses.h>
#include <stdexcept>
#include <string>

namespace Curses {

Color Color::Black(COLOR_BLACK);
Color Color::Red(COLOR_RED);
Color Color::Green(COLOR_GREEN);
Color Color::Yellow(COLOR_YELLOW);
Color Color::Blue(COLOR_BLUE);
Color Color::Magenta(COLOR_MAGENTA);
Color Color::Cyan(COLOR_CYAN);
Color Color::White(COLOR_WHITE);

Color::Color(short fg_) :
    fg(fg_),
    pair_num(fg_ + 1)
{
}

int Color::init_color_pair() const
{
    return init_pair(pair_num, fg, COLOR_BLACK);
}

Screen::Screen()
{
    initscr();
    if (has_colors() == FALSE) {
        endwin();
        throw std::runtime_error("Terminal does not support colors\n");
    }
    start_color();
    init_color_pairs();
    curs_set(0);
    noecho();
    refresh();
    getmaxyx(stdscr, max_y, max_x);
}

Screen::~Screen()
{
    endwin();
}

void Screen::print_point(int x, int y, char sym, Color color) const
{
    mvaddch(y, x, sym | COLOR_PAIR(color.pair_num));
}

void Screen::refresh_screen() const
{
    refresh();
}

void Screen::clear_screen() const
{
    clear();
}

int Screen::get_max_x() const
{
    return max_x;
}

int Screen::get_max_y() const
{
    return max_y;
}

void Screen::init_color_pairs() const
{
    Color::Black.init_color_pair();
    Color::Red.init_color_pair();
    Color::Green.init_color_pair();
    Color::Yellow.init_color_pair();
    Color::Blue.init_color_pair();
    Color::Magenta.init_color_pair();
    Color::Cyan.init_color_pair();
    Color::White.init_color_pair();
}

};
