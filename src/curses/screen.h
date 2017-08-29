#ifndef SCREEN_H
#define SCREEN_H

#include <ncurses.h>

namespace Curses {

class Screen {
public:
    Screen(int stats_height_ = 2);
    ~Screen();
    void refresh_all();
private:
    WINDOW *field;
    WINDOW *stats;
    int max_x;
    int max_y;
    int stats_height;
};

};

#endif
