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

#ifndef TOROIDAL_GRID_H
#define TOROIDAL_GRID_H

#include "grid/grid.h"

#include <vector>

namespace Grid {

template <class T>
class ToroidalGrid : public Grid<T> {
public:
    using GridIterator = typename Grid<T>::GridIterator;
    using UnaryPredicate = typename Grid<T>::UnaryPredicate;

    ToroidalGrid(int size_x_, int size_y_);
    virtual ~ToroidalGrid() override;

    virtual T &operator()(int x, int y) override;
    virtual const T &operator()(int x, int y) const override;
    /* Get the Moore neigbors of a cell, omitting the center */
    virtual std::vector<T> moore_neighbors(const GridIterator &it) const override;
    /* Count the Moore neighbors of a cell matching the given predicate,
     * omitting the center.
     */
    virtual int moore_neighbors_cnt_if(const GridIterator &it, UnaryPredicate pred) const override;
};

template <class T>
ToroidalGrid<T>::ToroidalGrid(int size_x_, int size_y_) :
    Grid<T>(size_x_, size_y_)
{
}

template <class T>
ToroidalGrid<T>::~ToroidalGrid()
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

template <class T>
std::vector<T> ToroidalGrid<T>::moore_neighbors(const typename Grid<T>::GridIterator &it) const
{
    std::vector<T> neighbors;
    int v_pos = it - this->begin();
    int x_pos = v_pos / this->get_size_y();
    int y_pos = v_pos % this->get_size_y();
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            if (x == 0 && y == 0) {
                continue;
            }
            neighbors.push_back(this->operator()(x_pos + x, y_pos + y));
        }
    }
    return neighbors;
}

template <class T>
int ToroidalGrid<T>::moore_neighbors_cnt_if(const GridIterator &it, UnaryPredicate pred) const
{
    int v_pos = it - this->begin();
    int x_pos = v_pos / this->get_size_y();
    int y_pos = v_pos % this->get_size_y();
    int cnt = 0;
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            if (x == 0 && y == 0) {
                continue;
            }
            if (pred(this->operator()(x_pos + x, y_pos + y))) {
                ++cnt;
            }
        }
    }
    return cnt;
}

};

#endif
