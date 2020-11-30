#ifndef WINTER_GRID_H
#define WINTER_GRID_H

#include <cassert>

template <typename T>
class Grid
{
public:
    Grid(int width, int height, T default_value = T())
    {
        assert(width > 0 && height > 0 && "width and height must both be greater than zero");

        data = new T*[height];
        T* pool = new T[height * width]{default_value};

        for (unsigned i = 0; i < height; i++, pool += width )
        {
            data[i] = pool;
        }
    }

    ~Grid()
    {
        delete [] data[0];  // remove the pool
        delete [] data;     // remove the pointers
    }

    T*& operator[](int index)
    {
        return data[index];
    }

    const T*& operator[](int index) const
    {
        return data[index];
    }

private:
    T** data;
};

#endif // WINTER_GRID_H
