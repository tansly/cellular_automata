#include "automata/life.h"
#include "curses/screen.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>

int main(int argc, char **argv)
{
    Curses::Screen screen;
    Automata::Life automaton(screen.get_max_x(), screen.get_max_y());
    const int max_gen = 10000;
    int rate = 100000;
    if (argc == 2) {
        try {
            rate = std::stoi(std::string(argv[1]));
        } catch (const std::invalid_argument &ex) {
            std::cerr << "Invalid argument" << std::endl;
            return 1;
        }
    }
    while (automaton.get_curr_gen() < max_gen) {
        usleep(rate);
        automaton.draw(screen);
        automaton.update();
    }
    return 0;
}
