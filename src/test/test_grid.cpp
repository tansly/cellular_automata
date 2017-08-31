#include "grid/grid.h"

#include <iostream>

int main()
{
    Grid::Grid<int> grid(10, 15);
    std::cout << grid(3, 5) << std::endl;
}
