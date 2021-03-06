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

#ifndef SCREEN_H
#define SCREEN_H

#include "grid/grid.h"

#include <ncurses.h>
#include <string>

namespace Curses {

class Color {
public:
    Color() = delete;
    static Color Black;
    static Color Red;
    static Color Green;
    static Color Yellow;
    static Color Blue;
    static Color Magenta;
    static Color Cyan;
    static Color White;

private:
    Color(short fg_);
    int init_color_pair() const;

    const short fg;
    const short pair_num;

    friend class Screen;
};

class Screen {
public:
    Screen();
    ~Screen();

    Screen(const Screen &) = delete;
    Screen &operator=(const Screen &) = delete;

    int get_max_x() const;
    int get_max_y() const;

    void print_point(int x, int y, char sym, Color color) const;
    void refresh_screen() const;
    void clear_screen() const;
    /* Print a Grid of class T. The class T must provide two functions:
     * const Curses::Color &T::color() const;
     * char T::symbol() const;
     * First one returns the color, second returns the symbol to be printed
     * for the element.
     */
    template <class T>
    void draw_grid(const Grid::Grid<T> &grid) const;
    /* TODO: Document */
    template <class T>
    void read_grid(Grid::Grid<T> &grid) const;
private:
    void init_color_pairs() const;
    int max_x;
    int max_y;
};

template <class T>
void Screen::draw_grid(const Grid::Grid<T> &grid) const
{
    int bound_x = grid.get_size_x();
    int bound_y = grid.get_size_y();
    for (int x = 0; x < bound_x; ++x) {
        for (int y = 0; y < bound_y; ++y) {
            const T &el = grid(x, y);
            print_point(x, y, el.symbol(), el.color());
        }
    }
    refresh();
}

template <class T>
void Screen::read_grid(Grid::Grid<T> &grid) const
{
    int ch, x, y;
    draw_grid(grid);
    curs_set(1);
    move(0, 0);
    while ((ch = getch()) != '\n') {
        getyx(stdscr, y, x);
        switch (ch) {
            case 'h':
                move(y, x - 1);
                break;
            case 'j':
                move(y + 1, x);
                break;
            case 'k':
                move(y - 1, x);
                break;
            case 'l':
                move(y, x + 1);
                break;
            case ' ':
                if (x < grid.get_size_x() && y < grid.get_size_y()) {
                    T &curr = grid(x, y);
                    curr.toggle_state();
                    print_point(x, y, curr.symbol(), curr.color());
                    /* Make the cursor stay at the same spot */
                    move(y, x);
                }
                break;
            default:
                break;
        }
        refresh_screen();
    }
    curs_set(0);
    refresh_screen();
}

};

#endif
