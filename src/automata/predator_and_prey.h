#ifndef PREDATOR_AND_PREY_H
#define PREDATOR_AND_PREY_H

#include "curses/screen.h"
#include "grid/toroidal_grid.h"

#include <random>

namespace Automata {

class PredatorAndPrey {
public:
    explicit PredatorAndPrey(int size_x_, int size_y_, double prey_dr = 0.85,
            double predator_dr = 0.85);
    void update();
    void run(int gens);
    void draw(Curses::Screen &screen);

    int get_curr_gen() const;
private:
    struct Creature {
        enum CreatureType { PREDATOR, PREY, EMPTY };

        explicit Creature(CreatureType type_ = Creature::EMPTY);

        const Curses::Color &color() const;
        char symbol() const;

        CreatureType type;
    };

    bool out_of_field(int x, int y) const;

    const int size_x;
    const int size_y;
    Grid::ToroidalGrid<Creature> field;
    int curr_gen;
    std::mt19937 rng;
    std::bernoulli_distribution prey_disperse;
    std::bernoulli_distribution predator_disperse;
};

};

#endif
