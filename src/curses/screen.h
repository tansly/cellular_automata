#ifndef SCREEN_H
#define SCREEN_H

#include "grid/grid.h"

#include <ncurses.h>
#include <string>

namespace Curses {

class Color {
public:
    Color(short fg_);
    int init_color_pair();

    static Color Black;
    static Color Red;
    static Color Green;
    static Color Yellow;
    static Color Blue;
    static Color Magenta;
    static Color Cyan;
    static Color White;

    const short fg;
    const short pair_num;
};

class Screen {
public:
    Screen();
    ~Screen();

    Screen(const Screen &) = delete;
    Screen &operator=(const Screen &) = delete;

    int get_max_x() const;
    int get_max_y() const;

    void print_point(int x, int y, char sym, Color color);
    void refresh_screen();
    void clear_screen();
    /* Print a Grid of class T. The class T must provide two functions:
     * const Curses::Color &T::color() const;
     * char T::symbol() const;
     * First one returns the color, second returns the symbol to be printed
     * for the element.
     */
    template <class T>
    void draw_grid(const Grid::Grid<T> &grid);
private:

    int max_x;
    int max_y;
};

template <class T>
void Screen::draw_grid(const Grid::Grid<T> &grid)
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

};

#endif
