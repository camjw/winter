#ifndef WINTER_VEC_H
#define WINTER_VEC_H

#include <cstddef>
#include <cmath>

namespace maths
{
    template <typename T, std::size_t length>
    struct vec_base;

    template <typename T>
    struct vec_base<T, 2>
    {
        T x, y;

        vec_base() = default;

        constexpr explicit vec_base(T v)
            : x(v)
            , y(v)
        {
        }

        constexpr vec_base(T x, T y)
            : x(x)
            , y(y)
        {
        }

        constexpr T& operator[](std::size_t index) noexcept
        {
            switch (index)
            {
            case 0:
                return x;
            default:
                return y;
            }
        }

        constexpr const T& operator[](std::size_t index) const noexcept
        {
            switch (index)
            {
            case 0:
                return x;
            default:
                return y;
            }
        }
    };

    template <typename T>
    struct vec_base<T, 3>
    {
        T x, y, z;

        vec_base() = default;

        constexpr explicit vec_base(T v)
            : x(v)
            , y(v)
            , z(v)
        {
        }

        constexpr vec_base(T x, T y, T z)
            : x(x)
            , y(y)
            , z(z)
        {
        }

        constexpr vec_base(vec_base<T, 2> v, T z)
            : x(v.x)
            , y(v.y)
            , z(z)
        {
        }

        constexpr T& operator[](std::size_t index) noexcept
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

        constexpr const T& operator[](std::size_t index) const noexcept
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
    };

    template <typename T>
    struct vec_base<T, 4>
    {
        T x, y, z, w;

        vec_base() = default;

        constexpr explicit vec_base(T v)
            : x(v)
            , y(v)
            , z(v)
            , w(v)
        {
        }

        constexpr vec_base(T x, T y, T z, T w)
            : x(x)
            , y(y)
            , z(z)
            , w(w)
        {
        }

        constexpr vec_base(const vec_base<T, 2>& xy, T z, T w)
            : x(xy[0])
            , y(xy[1])
            , z(z)
            , w(w)
        {
        }

        constexpr vec_base(T x, const vec_base<T, 2>& yz, T w)
            : x(x)
            , y(yz[0])
            , z(yz[1])
            , w(w)
        {
        }

        constexpr vec_base(T x, T y, const vec_base<T, 2>& zw)
            : x(x)
            , y(y)
            , z(zw[0])
            , w(zw[1])
        {
        }

        constexpr vec_base(const vec_base<T, 2>& xy, const vec_base<T, 2>& zw)
            : x(xy[0])
            , y(xy[1])
            , z(zw[0])
            , w(zw[1])
        {
        }

        constexpr vec_base(const vec_base<T, 3>& xyz, T w)
            : x(xyz[0])
            , y(xyz[1])
            , z(xyz[2])
            , w(w)
        {
        }

        constexpr vec_base(T x, const vec_base<T, 3>& yzw)
            : x(x)
            , y(yzw[0])
            , z(yzw[1])
            , w(yzw[2])
        {
        }

        constexpr T& operator[](std::size_t index) noexcept
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

        constexpr const T& operator[](std::size_t index) const noexcept
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
    };

    template <typename T, std::size_t length>
    struct vec : vec_base<T, length>
    {
        using vec_base<T, length>::vec_base;

        vec() = default;

        vec(vec&&) = default;
        vec& operator=(vec&&) = default;

        vec(const vec&) = default;
        vec& operator=(const vec&) = default;

        operator float*() { return reinterpret_cast<float*>(this); }

        static constexpr std::size_t size = length;

        static vec constant(T t)
        {
            vec output;

            for (int i = 0; i < size; i++)
            {
                output[i] = t;
            }

            return output;
        }

        static vec zero()
        {
            return constant(0);
        }

        static vec one()
        {
            return constant(1);
        }

        vec<T, length> normalise()
        {
            T vec_magnitude = magnitude();
            vec<T, length> output;

            for (std::size_t i = 0; i < length; i++)
            {
                output[i] = (*this)[i] / vec_magnitude;
            }

            return output;
        }

        constexpr T square_magnitude()
        {
            T output = 0;
            for (std::size_t i = 0; i < length; i++)
            {
                output += this->operator[](i) * this->operator[](i);
            }

            return output;
        }

        constexpr T magnitude()
        {
            return std::sqrt(square_magnitude());
        }
    };
}

using int2 = maths::vec<int, 2>;
using int3 = maths::vec<int, 3>;
using int4 = maths::vec<int, 4>;

using uint2 = maths::vec<unsigned, 2>;
using uint3 = maths::vec<unsigned, 3>;
using uint4 = maths::vec<unsigned, 4>;

using bool2 = maths::vec<bool, 2>;
using bool3 = maths::vec<bool, 3>;
using bool4 = maths::vec<bool, 4>;

using float2 = maths::vec<float, 2>;
using float3 = maths::vec<float, 3>;
using float4 = maths::vec<float, 4>;

using char2 = maths::vec<char, 2>;
using char3 = maths::vec<char, 3>;
using char4 = maths::vec<char, 4>;

#endif // WINTER_VEC_H
