#ifndef SCREEN_H
#define SCREEN_H

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
    Screen(int stats_height_ = 1);
    ~Screen();

    Screen(const Screen &) = delete;
    Screen &operator=(const Screen &) = delete;

    void clear_field();
    void clear_stats();
    void print_point(int x, int y, char sym, Color color);
    void print_stats(std::string &&str);
    void refresh_all();

    int get_max_x() const;
    int get_max_y() const;
private:
    WINDOW *field;
    WINDOW *stats;
    int max_x;
    int max_y;
    int stats_height;
};

};

#endif
