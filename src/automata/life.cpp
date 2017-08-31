#include "automata/life.h"
#include "curses/screen.h"
#include "grid/toroidal_grid.h"

#include <random>

namespace Automata {

Life::Cell::Cell(State state_) :
    state(state_)
{
}

const Curses::Color &Life::Cell::color() const
{
    return state == ALIVE ? Curses::Color::White : Curses::Color::Black;
}

char Life::Cell::symbol() const
{
    return '*';
}

Life::Life(int size_x_, int size_y_) :
    size_x(size_x_),
    size_y(size_y_),
    grid(size_x, size_y),
    curr_gen(0)
{
    std::mt19937 rng {std::random_device()()};
    std::uniform_int_distribution<int> rndint(0, 2);
    for (int x = 0; x < size_x; ++x) {
        for (int y = 0; y < size_y; ++y) {
            int t = rndint(rng);
            switch (t) {
                case 0:
                    grid(x, y) = Cell(Cell::ALIVE);
                    break;
                case 1:
                    /* FALLTHROUGH */
                case 2:
                    grid(x, y) = Cell(Cell::DEAD);
                    break;
            }
        }
    }
}

void Life::update()
{
    decltype(grid) new_grid(size_x, size_y);
    for (int x = 0; x < size_x; ++x) {
        for (int y = 0; y < size_y; ++y) {
            int neighbors = 0;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if (i == 0 && j == 0) {
                        continue;
                    }
                    if (grid(x + i, y + j).state == Cell::ALIVE) {
                        ++neighbors;
                    }
                }
            }
            if (grid(x, y).state == Cell::ALIVE) {
                if (neighbors < 2 || neighbors > 3) {
                    new_grid(x, y) = Cell(Cell::DEAD);
                } else {
                    new_grid(x, y) = Cell(Cell::ALIVE);
                }
            } else {
                if (neighbors == 3) {
                    new_grid(x, y) = Cell(Cell::ALIVE);
                }
            }
        }
    }
    grid = std::move(new_grid);
    ++curr_gen;
}

void Life::draw(Curses::Screen &screen) const
{
    screen.draw_grid(grid);
}

int Life::get_curr_gen() const
{
    return curr_gen;
}

};
