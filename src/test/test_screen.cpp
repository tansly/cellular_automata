#include "curses/screen.h"

#include <ncurses.h>
#include <random>
#include <sstream>

int main()
{
    Curses::Screen screen;
    std::random_device r;
    std::default_random_engine gen(r());
    std::uniform_int_distribution<int> randint(0, 2);
    for (;;) {
        screen.clear_field();
        for (int i = 0; i < 1000; i++) {
            for (int j = 0; j < 1000; j++) {
                int color = randint(gen);
                if (color == 0) {
                    screen.print_point(i, j, '*', Curses::Color::Red);
                } else if (color == 1) {
                    screen.print_point(i, j, '*', Curses::Color::Green);
                } else {
                    screen.print_point(i, j, '*', Curses::Color::Black);
                }
            }
        }
        screen.clear_stats();
        screen.print_stats("This is a test");
        screen.refresh_all();
    }
    return 0;
}
