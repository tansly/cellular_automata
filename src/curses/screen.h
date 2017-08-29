#ifndef SCREEN_H
#define SCREEN_H

#include <ncurses.h>

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
    Screen(int stats_height_ = 2);
    ~Screen();

    Screen(const Screen &) = delete;
    Screen &operator=(const Screen &) = delete;

    void draw_point(int x, int y, char sym, Color color);
    void redraw_all();
private:
    WINDOW *field;
    WINDOW *stats;
    int max_x;
    int max_y;
    int stats_height;
};

};

#endif
