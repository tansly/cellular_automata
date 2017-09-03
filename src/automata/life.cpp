#include "automata/life.h"
#include "curses/screen.h"
#include "grid/toroidal_grid.h"

#include <algorithm>
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
    for (auto it = grid.begin(); it != grid.end(); ++it) {
        int t = rndint(rng);
        switch (t) {
            case 0:
                *it = Cell(Cell::ALIVE);
                break;
            case 1:
                /* FALLTHROUGH */
            case 2:
                *it = Cell(Cell::DEAD);
                break;
        }
    }
}

void Life::update()
{
    /* TODO: Should we allocate the temporary grid for once during object
     * construction (and reuse it) or is this fine?
     * Does this cause any noticeable overhead?
     */
    decltype(grid) new_grid(size_x, size_y);
    auto it = grid.begin();
    auto new_it = new_grid.begin();
    for (/* it, new_it */; it != grid.end(); ++it, ++new_it) {
        /* TODO: We allocate a new vector on every iteration,
         * and this is obviously inefficient.
         * Think of something else here (if the allocation overhead is not negligible)
         * while keeping the simplicity of this method. Would it be good if
         * the grid method took a vector as reference from us and filled it, so
         * we could create a vector here and reuse it at every iteration?
         * Is there a better way?
         */
        auto neighbors = grid.moore_neighbors(it);
        int neighbor_cnt = std::count_if(neighbors.begin(), neighbors.end(),
                [](const Cell &cell){return cell.state == Cell::ALIVE;});
        if (it->state == Cell::ALIVE) {
            if (neighbor_cnt < 2 || neighbor_cnt > 3) {
                *new_it = Cell(Cell::DEAD);
            } else {
                *new_it = Cell(Cell::ALIVE);
            }
        } else {
            if (neighbor_cnt == 3) {
                *new_it = Cell(Cell::ALIVE);
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

unsigned long Life::get_curr_gen() const
{
    return curr_gen;
}

};
