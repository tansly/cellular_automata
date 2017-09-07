/*
    Cellular automaton visualization in C++, using ncurses
    Copyright (C) 2017 Yağmur Oymak

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "automata/life_like.h"

#include <random>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

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
    return state == ALIVE ? '*' : ' ';
}

void LifeLike::Cell::toggle_state()
{
    switch (state) {
        case ALIVE:
            state = DEAD;
            break;
        case DEAD:
            state = ALIVE;
            break;
    }
}

LifeLike::LifeLike(int size_x, int size_y, const std::string &rule) :
    rule_born(8),
    rule_survive(8),
    grid(size_x, size_y),
    curr_gen(0)
{
    init_rules(rule);
    init_rnd_grid();
}

LifeLike::LifeLike(Grid::ToroidalGrid<Cell> ngrid, const std::string &rule) :
    rule_born(8),
    rule_survive(8),
    grid(std::move(ngrid)),
    curr_gen(0)
{
    init_rules(rule);
}

void LifeLike::update()
{
    /* TODO: Should we allocate the temporary grid for once during object
     * construction (and reuse it) or is this fine?
     * Does this cause any noticeable overhead?
     */
    decltype(grid) new_grid(grid.get_size_x(), grid.get_size_y());
    auto it = grid.begin();
    auto new_it = new_grid.begin();
    for (/* it, new_it */; it != grid.end(); ++it, ++new_it) {
        int neighbor_cnt = grid.moore_neighbors_cnt_if(it,
                [](const Cell &cell){return cell.state == Cell::ALIVE;});
        if (it->state == Cell::ALIVE) {
            /* Alive cell, check for survival */
            if (rule_survive[neighbor_cnt]) {
                *new_it = Cell(Cell::ALIVE);
            } else {
                /* Neighbor count not found in survive rule */
                *new_it = Cell(Cell::DEAD);
            }
        } else {
            /* Dead cell, check for new born */
            if (rule_born[neighbor_cnt]) {
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

unsigned long LifeLike::get_curr_gen() const
{
    return curr_gen;
}

void LifeLike::init_rnd_grid()
{
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

void LifeLike::init_rules(const std::string &rule)
{
    /* Initialize the rules */
    std::regex valid_rulestring("B[0-8]*/S[0-8]*");
    if (!std::regex_match(rule, valid_rulestring)) {
        throw std::invalid_argument("LifeLike::LifeLike(): Bad rulestring");
    }
    int i;
    for (i = 1; rule[i] != '/'; ++i) {
        rule_born[rule[i] - '0'] = true;
    }
    for (i += 2; rule[i]; ++i) {
        rule_survive[rule[i] - '0'] = true;
    }
}

};
