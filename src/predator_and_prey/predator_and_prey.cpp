#include "curses/screen.h"
#include "grid/grid.h"

#include <memory>
#include <map>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

class PredatorAndPrey {
public:
    explicit PredatorAndPrey(double prey_dr = 0.85, double predator_dr = 0.85);
    void update();
    void run(int gens);
    void draw();

    int get_curr_gen() const;
private:
    struct Creature {
        enum CreatureType { PREDATOR, PREY, EMPTY };

        explicit Creature(CreatureType type_ = Creature::EMPTY);

        const Curses::Color &color() const;

        CreatureType type;
    };

    bool out_of_field(int x, int y) const;

    Curses::Screen screen;
    /* Field size is bound to the screen size at startup and does not change.
     * TODO: Implement resizing to match the screen size.
     */
    const int size_x;
    const int size_y;
    Grid::Grid<Creature> field;
    int curr_gen;
    std::mt19937 rng;
    std::bernoulli_distribution prey_disperse;
    std::bernoulli_distribution predator_disperse;
};

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

PredatorAndPrey::PredatorAndPrey(double prey_dr, double predator_dr) :
    screen(0),
    size_x(screen.get_max_x() + 1),
    size_y(screen.get_max_y() + 1),
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
                        if (!out_of_field(x + i, y + j) &&
                                field(x + i, y + j).type == Creature::EMPTY) {
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
                        if (!out_of_field(x + i, y + j) &&
                                field(x + i, y + j).type == Creature::PREY) {
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
                        if (!out_of_field(x + i, y + j) &&
                                new_field(x + i, y + j).type == Creature::PREY) {
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
}

void PredatorAndPrey::run(int gens)
{
    for (int i = 0; i < gens; ++i) {
        update();
    }
}

void PredatorAndPrey::draw()
{
    /* TODO: Print statistics to some target. Either to an external file,
     * or stderr or on the screen if there is a way to print on the ncurses
     * window without clearing the window everytime. (Clearing causes the whole
     * terminal to flicker
     */
    /* The minimum of the field size or the screen size should be drawn.
     * TODO: Implement proper resizing of the field to match the screen size
     * so this kind of stuff is not necessary.
     */
    int bound_x = std::min(size_x, screen.get_max_x() + 1);
    int bound_y = std::min(size_y, screen.get_max_y() + 1);
    for (int x = 0; x < bound_x; ++x) {
        for (int y = 0; y < bound_y; ++y) {
            screen.print_point(x, y, '*', field(x, y).color());
        }
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
        automaton.draw();
        automaton.run(1);
    }
    return 0;
}
