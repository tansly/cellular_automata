#ifndef GRID_H
#define GRID_H

#include <vector>

/* TODO: Implement resizing?
 * Do bounds checking (maybe not)?
 */

namespace Grid {

template <class T>
class Grid {
public:
    Grid(int size_x_, int size_y_);
    T &operator()(int x, int y);
    const T &operator()(int x, int y) const;

    int get_size_x() const;
    int get_size_y() const;
private:
    std::vector<T> vec;
    int size_x;
    int size_y;
};

template <class T>
Grid<T>::Grid(int size_x_, int size_y_) :
    vec(size_x_ * size_y_),
    size_x(size_x_),
    size_y(size_y_)
{
}

template <class T>
T &Grid<T>::operator()(int x, int y)
{
    return vec[x * size_y + y];
}

template <class T>
const T &Grid<T>::operator()(int x, int y) const
{
    return vec[x * size_y + y];
}

template <class T>
int Grid<T>::get_size_x() const
{
    return size_x;
}

template <class T>
int Grid<T>::get_size_y() const
{
    return size_y;
}

};

#endif
