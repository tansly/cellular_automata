#ifndef GRID_H
#define GRID_H

#include <vector>

namespace Grid {

template <class T>
class Grid {
public:
    typedef typename std::vector<T>::iterator GridIterator;

    Grid(int size_x_, int size_y_);
    virtual ~Grid();

    virtual T &operator()(int x, int y);
    virtual const T &operator()(int x, int y) const;
    /* Get the Moore neigbors of a cell, omitting the center */
    virtual std::vector<T> moore_neighbors(const GridIterator &it) const;


    auto begin();
    auto begin() const;
    auto end();
    auto end() const;

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
Grid<T>::~Grid()
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
auto Grid<T>::begin()
{
    return vec.begin();
}

template <class T>
auto Grid<T>::begin() const
{
    return vec.begin();
}

template <class T>
auto Grid<T>::end()
{
    return vec.end();
}

template <class T>
auto Grid<T>::end() const
{
    return vec.end();
}

template <class T>
std::vector<T> Grid<T>::moore_neighbors(const GridIterator &it) const
{
    std::vector<T> neighbors;
    int v_pos = it - this->begin();
    int x_pos = v_pos / size_y;
    int y_pos = v_pos % size_y;
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            if (x_pos + x < 0 || x_pos + x >= size_x ||
                    y_pos + y < 0 || y_pos + y >= size_y ||
                    (x == 0 && y == 0)) {
                continue;
            }
            neighbors.push_back(this->operator()(x_pos + x, y_pos + y));
        }
    }
    return neighbors;
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
