#include "automata/life_like.h"

#include <random>
#include <regex>
#include <stdexcept>
#include <string>

namespace Automata {

LifeLike::Cell::Cell(State nstate) :
    state(nstate)
{
}

const Curses::Color &LifeLike::Cell::color() const
{
    return state == ALIVE ? Curses::Color::White : Curses::Color::Black;
}

char LifeLike::Cell::symbol() const
{
    return '*';
}


LifeLike::LifeLike(int nsize_x, int nsize_y, const std::string &rule) :
    size_x(nsize_x),
    size_y(nsize_y),
    grid(size_x, size_y),
    curr_gen(0)
{
    /* Initialize the rules */
    std::regex valid_rulestring("B[0-9]*/S[0-9]*");
    if (!std::regex_match(rule, valid_rulestring)) {
        throw std::invalid_argument("LifeLike::LifeLike(): Bad rulestring");
    }
    auto n = rule.find("/S");
    rule_born = rule.substr(1, n - 1);
    rule_survive = rule.substr(n + 2);
    /* Initialize the grid */
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

void LifeLike::update()
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
            /* Alive cell, check for survival */
            if (rule_survive.find('0' + neighbor_cnt) != std::string::npos) {
                *new_it = Cell(Cell::ALIVE);
            } else {
                /* Neighbor count not found in survive rule */
                *new_it = Cell(Cell::DEAD);
            }
        } else {
            /* Dead cell, check for new born */
            if (rule_born.find('0' + neighbor_cnt) != std::string::npos) {
                *new_it = Cell(Cell::ALIVE);
            }
        }
    }
    grid = std::move(new_grid);
    ++curr_gen;
}

void LifeLike::draw(Curses::Screen &screen) const
{
    screen.draw_grid(grid);
}


};
