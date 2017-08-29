#include "curses/screen.h"

#include <ncurses.h>
#include <stdexcept>

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

int Color::init_color_pair()
{
    return init_pair(pair_num, fg, COLOR_BLACK);
}

namespace {

void init_color_pairs()
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

Screen::Screen(int stats_height_) :
    stats_height(stats_height_)
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
    getmaxyx(stdscr, max_y, max_x);
    field = newwin(max_y - stats_height, max_x, 0, 0);
    stats = newwin(stats_height, max_x, max_y - stats_height, 0);
    box(stats, 0, 0);
    refresh();
    wrefresh(field);
    wrefresh(stats);
}

Screen::~Screen()
{
    endwin();
}

void Screen::redraw_all()
{
    int new_x, new_y;
    getmaxyx(stdscr, new_y, new_x);
    if (new_x != max_x || new_y != max_y) {
        max_x = new_x;
        max_y = new_y;
        wresize(field, max_y - stats_height, max_x);
        wresize(stats, stats_height, max_x);
        mvwin(stats, max_y - stats_height, 0);
        wclear(stdscr);
        wclear(field);
        wclear(stats);
        box(stats, 0, 0);
    }
    refresh();
    wrefresh(field);
    wrefresh(stats);
}

void Screen::draw_point(int x, int y, char sym, Color color)
{
    mvwaddch(field, y, x, sym | COLOR_PAIR(color.pair_num));
}

};
