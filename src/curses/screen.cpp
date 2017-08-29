#include "curses/screen.h"

namespace Curses {

Screen::Screen(int stats_height_) :
    stats_height(stats_height_)
{
    initscr();
    noecho();
    getmaxyx(stdscr, max_y, max_x);
    field = newwin(max_y - stats_height, max_x, 0, 0);
    stats = newwin(stats_height, max_x, max_y - stats_height, 0);
    box(stats, 0, 0);
    wrefresh(field);
    wrefresh(stats);
}

Screen::~Screen()
{
    endwin();
}

void Screen::refresh_all()
{
    wrefresh(field);
    wrefresh(stats);
}

};
