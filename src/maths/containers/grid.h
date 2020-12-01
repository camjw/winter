#ifndef WINTER_GRID_H
#define WINTER_GRID_H

#include <cassert>

template <typename T>
class Grid
{
public:
    Grid(int width, int height, T default_value = T())
        : width(width)
        , height(height)
    {
        assert(width > 0 && height > 0 && "width and height must both be greater than zero");

        data = new T*[height];
        T* pool = new T[height * width] { default_value };

        for (unsigned i = 0; i < height; i++, pool += width)
        {
            data[i] = pool;
        }
    }

    ~Grid()
    {
        delete[] data[0]; // remove the pool
        delete[] data; // remove the pointers
    }

    Grid& operator= ( const Grid & other)
    {
        if(&other == this)
        {
            return *this;
        }
    }


    Grid(const Grid& other)
        : width(other.width)
    , height(other.height)
    {
        data = new T*[height];
        T* pool = new T[height * width];

        for (unsigned i = 0; i < height; i++, pool += width)
        {
            data[i] = pool;
        }

        for (int i = 0; i < height; i++)
        {
            T* other_row = other[i];
            for (int j = 0; j < width; j++)
            {
                data[i][j] = other_row[j];
            }
        }
    }

    T* operator[](int index)
    {
        return data[index];
    }

    const T* operator[](int index) const
    {
        return data[index];
    }

    int width;
    int height;

private:
    T** data;
};

#endif // WINTER_GRID_H
