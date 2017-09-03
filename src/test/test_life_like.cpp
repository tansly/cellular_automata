#include "automata/life_like.h"
#include "curses/screen.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << argv[0] << " rulestring" << std::endl;
        return 1;
    }
    Curses::Screen screen;
    try {
        Automata::LifeLike automaton(screen.get_max_x(), screen.get_max_y(), argv[1]);
        const int rate = 100000;
        for (;;) {
            usleep(rate);
            automaton.draw(screen);
            automaton.update();
        }
    } catch (const std::invalid_argument &ex) {
        /* TODO: This does not print to the screen, do it some other way */
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
