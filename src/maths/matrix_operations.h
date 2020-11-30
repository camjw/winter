#ifndef WINTER_MATRIX_OPERATIONS_H
#define WINTER_MATRIX_OPERATIONS_H

#include "matrix.h"
#include "vec_operations.h"
#include <functional>
#include <cmath>

namespace maths
{
    template <typename T>
    constexpr T determinant(matrix<T, 2>& mat)
    {
        return mat.x[0] * mat.y[1] - mat.x[1] * mat.y[0];
    }

    template <typename T, std::size_t side_length>
    constexpr T determinant(matrix<T, side_length>& mat)
    {
        T output = 0;

        for (std::size_t i = 0; i < side_length; i++)
        {
            output += pow(-1, i) * mat.x[i] * determinant(principal_minor(mat, i));
        }

        return output;
    }

    template <typename T, std::size_t side_length>
    constexpr matrix<T, side_length - 1> principal_minor(matrix<T, side_length> mat, std::size_t column_index)
    {
        matrix<T, 3> output;
        std::size_t counter = 0;
        for (std::size_t i = 0; i < 4; i ++)
        {
            if (i == column_index)
            {
                continue;
            }

            for (std::size_t j = 0; j < side_length - 1; j++)
            {
                output[j][counter] = mat[j][i];
            }

            counter++;
        }
    }

    // operator +
    template <typename T, std::size_t side_length>
    constexpr matrix<T, side_length> operator+(const matrix<T, side_length>& m, const matrix<T, side_length>& n)
    {
        matrix<T, side_length> output;
        for (std::size_t i = 0; i < side_length; i++)
        {
            for (std::size_t j = 0; i < side_length; i++)
            {
                output[i][j] = m[i][j] + n[i][j];
            }
        }

        return output;
    }

    // operator +=
    template <typename T, std::size_t side_length>
    constexpr matrix<T, side_length>& operator+=(matrix<T, side_length>& m, const matrix<T, side_length>& n)
    {
        for (std::size_t i = 0; i < side_length; i++)
        {
            for (std::size_t j = 0; j < side_length; j++)
            {
                m[i][j] += n[i][j];
            }
        }

        return m;
    }

    // operator -
    template <typename T, std::size_t side_length>
    constexpr matrix<T, side_length> operator-(const matrix<T, side_length>& v, const matrix<T, side_length>& w)
    {
        matrix<T, side_length> output;
        for (std::size_t i = 0; i < side_length; i++)
        {
            for (std::size_t j = 0; j < side_length; j++)
            {
                output[i][j] = v[i][j] - w[i][j];
            }
        }

        return output;
    }

    // operator -=
    template <typename T, std::size_t side_length>
    constexpr matrix<T, side_length>& operator-=(matrix<T, side_length>& v, const matrix<T, side_length>& w)
    {
        for (std::size_t i = 0; i < side_length; i++)
        {
            for (std::size_t j = 0; j < side_length; j++)
            {
                v[i][j] -= w[i][j];
            }
        }

        return v;
    }

    // operator *
    template <typename T, std::size_t side_length>
    constexpr matrix<T, side_length> operator*(const matrix<T, side_length>& mat, T t)
    {
        matrix<T, side_length> output;
        for (std::size_t i = 0; i < side_length; i++)
        {
            for (std::size_t j = 0; j < side_length; j++)
            {
                output[i] = mat[i] * t;
            }
        }

        return output;
    }

    template <typename T, std::size_t side_length>
    constexpr matrix<T, side_length> operator*(T t, const matrix<T, side_length>& mat)
    {
        matrix<T, side_length> output;
        for (std::size_t i = 0; i < side_length; i++)
        {
            for (std::size_t j = 0; j < side_length; j++)
            {
                output[i] = t * mat[i];
            }
        }

        return output;
    }

    template <typename T, std::size_t length>
    constexpr matrix<T, length> operator*(const matrix<T, length>& v, const matrix<T, length>& w)
    {
        matrix<T, length> output;
        for (std::size_t i = 0; i < length; i++)
        {
            for (std::size_t j = 0; j < length; j++)
            {
                output[i][j] = maths::dot(v.row(i), w.column(j));
            }
        }

        return output;
    }

    template <typename T, std::size_t length>
    matrix<T, length> operator*(matrix<T, length>& v, matrix<T, length>& w)
    {
        matrix<T, length> output;
        for (std::size_t i = 0; i < length; i++)
        {
            for (std::size_t j = 0; j < length; j++)
            {
                output[i][j] = maths::dot(v.row(i), w.column(j));
            }
        }

        return output;
    }

    template <typename T, std::size_t length>
    constexpr vec<T, length> operator*(const matrix<T, length>& mat, const vec<T, length>& v)
    {
        vec<T, length> output;
        for (std::size_t i = 0; i < length; i++)
        {
            output[i] = maths::dot(mat[i], v);
        }

        return output;
    }

    // operator*=

    template <typename T, std::size_t side_length>
    constexpr matrix<T, side_length>& operator*=(matrix<T, side_length>& mat, T t)
    {
        for (std::size_t i = 0; i < side_length; i++)
        {
            for (std::size_t j = 0; j < side_length; j++)
            {
                mat[i][j] *= t;
            }
        }

        return mat;
    }

    template <typename T, std::size_t length>
    constexpr matrix<T, length>& operator*=(matrix<T, length>& v, const matrix<T, length>& w)
    {
        matrix<T, length> output;
        for (std::size_t i = 0; i < length; i++)
        {
            for (std::size_t j = 0; j < length; j++)
            {
                output[i] = maths::dot(v.row(i), w.column(j));
            }
        }

        v = output;
        return v;
    }

    // operator/

    template <typename T, std::size_t length>
    constexpr matrix<T, length> operator/(const matrix<T, length>& v, T t)
    {
        matrix<T, length> output;
        for (std::size_t i = 0; i < length; i++)
        {
            for (std::size_t j = 0; j < length; j++)
            {
                output[i][j] = v[i][j] / t;
            }
        }

        return output;
    }

    // operator/=

    template <typename T, std::size_t length>
    constexpr matrix<T, length>& operator/=(matrix<T, length>& v, T t)
    {
        for (std::size_t i = 0; i < length; i++)
        {
            for (std::size_t j = 0; j < length; j++)
            {
                v[i][j] /= t;
            }
        }

        return v;
    }

    // operator==

    template <typename T, std::size_t length>
    constexpr bool operator==(const matrix<T, length>& v, const matrix<T, length>& w)
    {
        for (std::size_t i = 0; i < length; i++)
        {
            for (std::size_t j = 0; j < length; j++)
            {
                if (v[i][j] != w[i][j])
                {
                    return false;
                }
            }
        }

        return true;
    }

    template <typename T, std::size_t length>
    constexpr bool operator!=(const matrix<T, length>& v, const matrix<T, length>& w)
    {
        for (std::size_t i = 0; i < length; i++)
        {
            for (std::size_t j = 0; j < length; j++)
            {
                if (v[i][j] == w[i][j])
                {
                    return false;
                }
            }
        }

        return true;
    }

    template <typename T, std::size_t side_length>
    std::size_t hash(const matrix<T, side_length>& mat) noexcept
    {
        std::size_t output = std::hash<T>(mat[0][0]);

        for (std::size_t i = 0; i < side_length; i++)
        {
            for (std::size_t j = 0; j < side_length; j++)
            {
                output = hash_combine_matrix(output, std::hash<T>(mat[i][j]));
            }
        }

        return output;
    }

    // A simple algorithm for combining two hash values,
    // algorithm from boost: http://www.boost.org/doc/libs/1_61_0/doc/html/hash/reference.html#boost.hash_combine
    constexpr inline std::size_t hash_combine_matrix(std::size_t hash1, std::size_t hash2)
    {
        return hash1 ^ (hash2 * 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
    }
}

namespace std
{
    template <typename T, std::size_t side_length>
    struct hash<maths::matrix<T, side_length>>
    {
        std::size_t operator()(const maths::matrix<T, side_length>& mat) const noexcept
        {
            return maths::hash(mat);
        }
    };
}

#endif // WINTER_MATRIX_OPERATIONS_H
