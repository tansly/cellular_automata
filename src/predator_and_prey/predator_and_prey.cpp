#include "curses/screen.h"

#include <memory>
#include <map>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

class PredatorAndPrey {
public:
    PredatorAndPrey(double prey_dr_ = 0.2, double pred_dr_ = 0.1,
            double pred_br_ = 0.8);
    void update();
    void run(int gens);
    void draw();

    int get_curr_gen() const;
private:
    struct Creature {
        enum CreatureType { PREDATOR, PREY, EMPTY };

        Creature();
        Creature(CreatureType type_);
        Creature(int type_);
        const Curses::Color &color() const;

        CreatureType type;
    };

    bool out_of_screen(int x, int y) const;

    Curses::Screen screen;
    std::map<std::pair<int, int>, Creature> field;
    int curr_gen;
    std::mt19937 rng;
    std::bernoulli_distribution prey_die;
    std::bernoulli_distribution pred_die;
    std::bernoulli_distribution pred_born;
};

PredatorAndPrey::Creature::Creature() :
    type(EMPTY)
{
}

PredatorAndPrey::Creature::Creature(CreatureType type_)
{
    type = type_;
}

PredatorAndPrey::Creature::Creature(int type_)
{
    switch (type_) {
        case 0:
            type = PREDATOR;
            break;
        case 1:
            type = PREY;
            break;
        case 2:
            type = EMPTY;
            break;
        default:
            throw std::invalid_argument("Bad creature type");
    }
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

PredatorAndPrey::PredatorAndPrey(double prey_dr, double pred_dr, double pred_br) :
    screen(0),
    curr_gen(0),
    rng(std::random_device()()),
    prey_die(prey_dr),
    pred_die(pred_dr),
    pred_born(pred_br)
{
    int max_x = screen.get_max_x();
    int max_y = screen.get_max_y();
    std::uniform_int_distribution<int> rndint(0, 2);
    for (int x = 0; x < max_x; ++x) {
        for (int y = 0; y < max_y; ++y) {
            int t = rndint(rng);
            field[{x, y}] = Creature(t);
        }
    }
}

bool PredatorAndPrey::out_of_screen(int x, int y) const
{
    return x < 0 || y < 0 ||
        x > screen.get_max_x() ||
        y > screen.get_max_y();
}

void PredatorAndPrey::update()
{
    decltype(field) new_field;
    for (auto cell : field) {
        auto coords = cell.first;
        int x = coords.first;
        int y = coords.second;
        Creature creature = cell.second;
        switch (creature.type) {
            case Creature::PREDATOR:
                if (!pred_die(rng)) {
                    /* Live another day */
                    new_field[coords] = creature;
                    /* Begin the hunt */
                    for (int i = -1; i <= 1; ++i) {
                        for (int j = -1; j <= 1; ++j) {
                            if (out_of_screen(x + i, y + j)) {
                                continue;
                            }
                            if (field[{x + i, y + j}].type == Creature::PREY &&
                                    pred_born(rng)) {
                                /* Go for the kill */
                                new_field[{x + i, y + j}] =
                                    Creature(Creature::PREDATOR);
                            }
                        }
                    }
                } else {
                    new_field[coords] = Creature(Creature::EMPTY);
                }
                break;
            case Creature::PREY:
                if (!prey_die(rng)) {
                    /* Live another day */
                    new_field[coords] = creature;
                    /* Look for empty spaces to reproduce */
                    for (int i = -1; i <= 1; ++i) {
                        for (int j = -1; j <= 1; ++j) {
                            if (out_of_screen(x + i, y + j)) {
                                continue;
                            }
                            if (field[{x + i, y + j}].type == Creature::EMPTY) {
                                /* Reproduce */
                                new_field[{x + i, y + j}] =
                                    Creature(Creature::PREY);
                            }
                        }
                    }
                } else {
                    new_field[coords] = Creature(Creature::EMPTY);
                }
                break;
            case Creature::EMPTY:
                new_field[coords] = Creature(Creature::EMPTY);
                break;
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

void PredatorAndPrey::draw()
{
    //std::ostringstream ss;
    //ss << "Generation: " << curr_gen;
    //screen.clear_stats();
    //screen.print_stats(ss.str());
    for (auto cell : field) {
        screen.print_point(cell.first.first, cell.first.second,
                '*', cell.second.color());
    }
    screen.refresh_all();
}

int PredatorAndPrey::get_curr_gen() const
{
    return curr_gen;
}

int main(int argc, char **argv)
{
    PredatorAndPrey automaton;
    const int max_gen = 10000;
    while (automaton.get_curr_gen() < max_gen) {
        automaton.run(1);
        automaton.draw();
    }
    return 0;
}
