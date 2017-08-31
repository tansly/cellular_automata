#include "automata/predator_and_prey.h"
#include "curses/screen.h"
#include "grid/grid.h"

#include <random>

namespace Automata {

PredatorAndPrey::Creature::Creature(CreatureType type_) :
    type(type_)
{
}

const Curses::Color &PredatorAndPrey::Creature::color() const
{
    switch (type) {
        case PREDATOR:
            return Curses::Color::Red;
        case PREY:
            return Curses::Color::Blue;
        case EMPTY:
            return Curses::Color::Black;
    }
}

char PredatorAndPrey::Creature::symbol() const
{
    return '*';
}

PredatorAndPrey::PredatorAndPrey(int size_x_, int size_y_, double prey_dr,
        double predator_dr) :
    size_x(size_x_),
    size_y(size_y_),
    field(size_x, size_y),
    curr_gen(0),
    rng(std::random_device()()),
    prey_disperse(prey_dr),
    predator_disperse(predator_dr)
{
    std::uniform_int_distribution<int> rndint(0, 3);
    for (int x = 0; x < size_x; ++x) {
        for (int y = 0; y < size_y; ++y) {
            /* Initialize with 1/4 prey, 1/4 predator and 1/2 empty */
            int t = rndint(rng);
            switch (t) {
                case 0:
                    field(x, y) = Creature(Creature::PREDATOR);
                    break;
                case 1:
                    field(x, y) = Creature(Creature::PREY);
                    break;
                case 2:
                    /* FALLTHROUGH */
                case 3:
                    field(x, y) = Creature(Creature::EMPTY);
                    break;
            }
        }
    }
}

bool PredatorAndPrey::out_of_field(int x, int y) const
{
    return x < 0 || y < 0 ||
        x >= size_x ||
        y >= size_y;
}

/* Algorithm from: http://www.rubinghscience.org/evol/spirals1.html
 */
void PredatorAndPrey::update()
{
    decltype(field) new_field(size_x, size_y);
    /* STEP 1: Disperse preys */
    for (int x = 0; x < size_x; ++x) {
        for (int y = 0; y < size_y; ++y) {
            if (field(x, y).type == Creature::PREY) {
                new_field(x, y) = Creature(Creature::PREY);
                /* Check the neighbors */
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        if (field(x + i, y + j).type == Creature::EMPTY) {
                            if (prey_disperse(rng)) {
                                new_field(x + i, y + j) =
                                    Creature(Creature::PREY);
                            }
                        }
                    }
                }
            }
        }
    }
    /* STEP 2: Disperse predators */
    for (int x = 0; x < size_x; ++x) {
        for (int y = 0; y < size_y; ++y) {
            if (field(x, y).type == Creature::PREDATOR) {
                new_field(x, y) = Creature(Creature::PREDATOR);
                /* Check the neighbors */
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        if (field(x + i, y + j).type == Creature::PREY) {
                            if (predator_disperse(rng)) {
                                new_field(x + i, y + j) =
                                    Creature(Creature::PREDATOR);
                            }
                        }
                    }
                }
            }
        }
    }
    /* STEP 3: Remove from the new-situation field all predators that do
     * not have a prey in at least one neighbour square.
     */
    for (int x = 0; x < size_x; ++x) {
        for (int y = 0; y < size_y; ++y) {
            if (new_field(x, y).type == Creature::PREDATOR) {
                bool has_contact = false;
                for (int i = -1; i <= 1 && !has_contact; ++i) {
                    for (int j = -1; j <= 1 && !has_contact; ++j) {
                        if (new_field(x + i, y + j).type == Creature::PREY) {
                            has_contact = true;
                        }
                    }
                }
                if (!has_contact) {
                    new_field(x, y) = Creature(Creature::EMPTY);
                }
            }
        }
    }
    field = std::move(new_field);
    ++curr_gen;
}

void PredatorAndPrey::run(int gens)
{
    for (int i = 0; i < gens; ++i) {
        update();
    }
}

void PredatorAndPrey::draw(Curses::Screen &screen)
{
    screen.draw_grid(field);
}

int PredatorAndPrey::get_curr_gen() const
{
    return curr_gen;
}

};
