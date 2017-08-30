#include "curses/screen.h"

#include <ncurses.h>
#include <random>

int main()
{
    Curses::Screen screen;
    std::random_device r;
    std::default_random_engine gen(r());
    std::uniform_int_distribution<int> randint(0, 2);
    for (;;) {
        for (int i = 0; i < 1000; i++) {
            for (int j = 0; j < 1000; j++) {
                int color = randint(gen);
                if (color == 0) {
                    screen.draw_point(i, j, '*', Curses::Color::Red);
                } else if (color == 1) {
                    screen.draw_point(i, j, '*', Curses::Color::Green);
                } else {
                    screen.draw_point(i, j, '*', Curses::Color::Black);
                }
            }
        }
        screen.redraw_all();
    }
    return 0;
}
