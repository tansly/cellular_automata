#ifndef TOROIDAL_GRID_H
#define TOROIDAL_GRID_H

#include "grid/grid.h"

#include <vector>

namespace Grid {

template <class T>
class ToroidalGrid : public Grid<T> {
public:
    ToroidalGrid(int size_x_, int size_y_);
    T &operator()(int x, int y);
    const T &operator()(int x, int y) const;
};

template <class T>
ToroidalGrid<T>::ToroidalGrid(int size_x_, int size_y_) :
    Grid<T>(size_x_, size_y_)
{
}

template <class T>
T &ToroidalGrid<T>::operator()(int x, int y)
{
    int nx = this->get_size_x();
    int ny = this->get_size_y();
    x = ((x % nx) + nx) % nx;
    y = ((y % ny) + ny) % ny;
    return Grid<T>::operator()(x, y);
}

template <class T>
const T &ToroidalGrid<T>::operator()(int x, int y) const
{
    int nx = this->get_size_x();
    int ny = this->get_size_y();
    x = ((x % nx) + nx) % nx;
    y = ((y % ny) + ny) % ny;
    return Grid<T>::operator()(x, y);
}

};

#endif
