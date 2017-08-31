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

void Screen::print_point(int x, int y, char sym, Color color)
{
    mvaddch(y, x, sym | COLOR_PAIR(color.pair_num));
}

void Screen::refresh_screen()
{
    refresh();
}

void Screen::clear_screen()
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

};
