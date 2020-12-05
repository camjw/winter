#ifndef WINTER_MATRIX_H
#define WINTER_MATRIX_H

#include <cstddef>
#include "vec.h"

// CAMERON: the vectors should be the _columns_ of the matrix so that
// this works nicely with OpenGL.

namespace maths
{

    template <typename T, std::size_t side_length>
    struct matrix_base;

    template <typename T>
    struct matrix_base<T, 2>
    {
        matrix_base() = default;

        vec<T, 2> x;
        vec<T, 2> y;

        constexpr vec<T, 2>& operator[](std::size_t index) noexcept
        {
            switch (index)
            {
            case 0:
                return x;
            default:
                return y;
            }
        }

        constexpr const vec<T, 2>& operator[](std::size_t index) const noexcept
        {
            switch (index)
            {
            case 0:
                return x;
            default:
                return y;
            }
        }

        constexpr const vec<T, 2> column(std::size_t index) const noexcept
        {
            return vec<T, 2>(x[index], y[index]);
        }
    };

    template <typename T>
    struct matrix_base<T, 3>
    {
        matrix_base() = default;

        vec<T, 3> x;
        vec<T, 3> y;
        vec<T, 3> z;

        constexpr vec<T, 3>& operator[](std::size_t index) noexcept
        {
            switch (index)
            {
            case 0:
                return x;
            case 1:
                return y;
            default:
                return z;
            }
        }

        constexpr const vec<T, 3>& operator[](std::size_t index) const noexcept
        {
            switch (index)
            {
            case 0:
                return x;
            case 1:
                return y;
            default:
                return z;
            }
        }

        constexpr const vec<T, 3> column(std::size_t index) const noexcept
        {
            return vec<T, 3>(x[index], y[index], z[index]);
        }
    };

    template <typename T>
    struct matrix_base<T, 4>
    {
        matrix_base() = default;

        vec<T, 4> x;
        vec<T, 4> y;
        vec<T, 4> z;
        vec<T, 4> w;

        constexpr vec<T, 4>& operator[](std::size_t index) noexcept
        {
            switch (index)
            {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                return w;
            }
        }

        constexpr const vec<T, 4>& operator[](std::size_t index) const noexcept
        {
            switch (index)
            {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                return w;
            }
        }

        constexpr const vec<T, 4> column(std::size_t index) const noexcept
        {
            return vec<T, 4>(x[index], y[index], z[index], w[index]);
        }
    };

    template <typename T, std::size_t side_length>
    struct matrix : matrix_base<T, side_length>
    {
        using matrix_base<T, side_length>::matrix_base;

        matrix() = default;

        matrix(matrix&&) = default;
        matrix& operator=(matrix&&) = default;

        matrix(const matrix&) = default;
        matrix& operator=(const matrix&) = default;

        operator float*() { return reinterpret_cast<float*>(this); }

        static matrix diagonal(T t)
        {
            matrix output = zero();

            for (int i = 0; i < side_length; i++)
            {
                output[i][i] = t;
            }

            return output;
        }

        static matrix diagonal(vec<T, side_length> v)
        {
            matrix output = zero();

            for (int i = 0; i < side_length; i++)
            {
                output[i][i] = v[i];
            }

            return output;
        }

        static matrix zero()
        {
            matrix output;
            for (std::size_t i = 0; i < side_length; i++)
            {
                for (std::size_t j = 0; j < side_length; j++)
                {
                    output[i][j] = 0;
                }
            }

            return output;
        }

        static matrix identity()
        {
            return diagonal(1);
        }

        constexpr const vec<T, side_length> row(std::size_t index) const noexcept
        {
            return this->operator[](index);
        }
    };
}


using int2x2 = maths::matrix<int, 2>;
using int3x3 = maths::matrix<int, 3>;
using int4x4 = maths::matrix<int, 4>;

using uint2x2 = maths::matrix<unsigned, 2>;
using uint3x3 = maths::matrix<unsigned, 3>;
using uint4x4 = maths::matrix<unsigned, 4>;

using bool2x2 = maths::matrix<bool, 2>;
using bool3x3 = maths::matrix<bool, 3>;
using bool4x4 = maths::matrix<bool, 4>;

using float2x2 = maths::matrix<float, 2>;
using float3x3 = maths::matrix<float, 3>;
using float4x4 = maths::matrix<float, 4>;

using char2x2 = maths::matrix<char, 2>;
using char3x3 = maths::matrix<char, 3>;
using char4x4 = maths::matrix<char, 4>;

#endif // WINTER_MATRIX_H
