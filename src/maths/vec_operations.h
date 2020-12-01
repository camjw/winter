#ifndef WINTER_VEC_OPERATIONS_H
#define WINTER_VEC_OPERATIONS_H

#include "vec.h"
#include <functional>
#include <cmath>

namespace maths
{
    template <typename T>
    constexpr vec<T, 3> cross(vec<T, 3> first, vec<T, 3> second)
    {
        return vec<T, 3>(
            first.y * second.z - first.z * second.y,
            first.z * second.x - first.x * second.z,
            first.x * second.y - first.y * second.x);
    }

    template <typename T, std::size_t length>
    constexpr T dot(vec<T, length> first, vec<T, length> second)
    {
        T output = T();

        for (int i = 0; i < length; i++)
        {
            output += first[i] * second[i];
        }

        return output;
    }

    template <typename T, std::size_t length>
    constexpr T square_magnitude(vec<T, length> v)
    {
        return dot(v, v);
    }

    template <typename T, std::size_t length>
    constexpr T magnitude(vec<T, length> v)
    {
        return std::sqrt(square_magnitude(v));
    }

    template <typename T, std::size_t length>
    constexpr vec<T, length> operator-(const vec<T, length>& v)
    {
        return v * -1;
    }

    // operator +
    template <typename T, std::size_t length>
    constexpr vec<T, length> operator+(const vec<T, length>& v, T t)
    {
        vec<T, length> output;
        for (std::size_t i = 0; i < length; i++)
        {
            output[i] = v[i] + t;
        }

        return output;
    }

    template <typename T, std::size_t length>
    constexpr vec<T, length> operator+(T t, const vec<T, length>& v)
    {
        vec<T, length> output;
        for (std::size_t i = 0; i < length; i++)
        {
            output[i] = v[i] + t;
        }

        return output;
    }

    template <typename T, std::size_t length>
    constexpr vec<T, length> operator+(const vec<T, length>& v, const vec<T, length>& w)
    {
        vec<T, length> output;
        for (std::size_t i = 0; i < length; i++)
        {
            output[i] = v[i] + w[i];
        }

        return output;
    }

    // operator +=
    template <typename T, std::size_t length>
    constexpr vec<T, length>& operator+=(vec<T, length>& v, T t)
    {
        for (std::size_t i = 0; i < length; i++)
        {
            v[i] += t;
        }

        return v;
    }

    template <typename T, std::size_t length>
    constexpr vec<T, length>& operator+=(vec<T, length>& v, const vec<T, length>& w)
    {
        for (std::size_t i = 0; i < length; i++)
        {
            v[i] += w[i];
        }

        return v;
    }

    template <typename T, std::size_t length>
    constexpr vec<T, length>& operator+=(vec<T, length>& v, vec<T, length>& w)
    {
        for (std::size_t i = 0; i < length; i++)
        {
            v[i] += w[i];
        }

        return v;
    }

    // operator -
    template <typename T, std::size_t length>
    constexpr vec<T, length> operator-(const vec<T, length>& v, T t)
    {
        vec<T, length> output;
        for (std::size_t i = 0; i < length; i++)
        {
            output[i] = v[i] - t;
        }

        return v;
    }

    template <typename T, std::size_t length>
    constexpr vec<T, length> operator-(T t, const vec<T, length>& v)
    {
        vec<T, length> output;
        for (std::size_t i = 0; i < length; i++)
        {
            output[i] = t - v[i];
        }

        return v;
    }

    template <typename T, std::size_t length>
    constexpr vec<T, length> operator-(const vec<T, length>& v, const vec<T, length>& w)
    {
        vec<T, length> output;
        for (std::size_t i = 0; i < length; i++)
        {
            output[i] = v[i] - w[i];
        }

        return output;
    }

    template <typename T, std::size_t length>
    constexpr vec<T, length> operator-(vec<T, length>& v, vec<T, length>& w)
    {
        vec<T, length> output;
        for (std::size_t i = 0; i < length; i++)
        {
            output[i] = v[i] - w[i];
        }

        return output;
    }

    // operator -=
    template <typename T, std::size_t length>
    constexpr vec<T, length>& operator-=(vec<T, length>& v, T t)
    {
        for (std::size_t i = 0; i < length; i++)
        {
            v[i] -= t;
        }

        return v;
    }

    template <typename T, std::size_t length>
    constexpr vec<T, length>& operator-=(vec<T, length>& v, const vec<T, length>& w)
    {
        for (std::size_t i = 0; i < length; i++)
        {
            v[i] -= w[i];
        }

        return v;
    }

    // operator *

    template <typename T, std::size_t length>
    constexpr vec<T, length> operator*(const vec<T, length>& v, T t)
    {
        vec<T, length> output;
        for (std::size_t i = 0; i < length; i++)
        {
            output[i] = v[i] * t;
        }

        return output;
    }

    template <typename T, std::size_t length>
    constexpr vec<T, length> operator*(T t, const vec<T, length>& v)
    {
        vec<T, length> output;
        for (std::size_t i = 0; i < length; i++)
        {
            output[i] = t * v[i];
        }

        return output;
    }

    template <typename T, std::size_t length>
    constexpr vec<T, length> operator*(const vec<T, length>& v, const vec<T, length>& w)
    {
        vec<T, length> output;
        for (std::size_t i = 0; i < length; i++)
        {
            output[i] = v[i] * w[i];
        }

        return output;
    }

    // operator*=

    template <typename T, std::size_t length>
    constexpr vec<T, length>& operator*=(vec<T, length>& v, T t)
    {
        for (std::size_t i = 0; i < length; i++)
        {
            v[i] *= t;
        }

        return v;
    }

    template <typename T, std::size_t length>
    constexpr vec<T, length>& operator*=(vec<T, length>& v, const vec<T, length>& w)
    {
        for (std::size_t i = 0; i < length; i++)
        {
            v[i] *= w[i];
        }

        return v;
    }

    // operator/

    template <typename T, std::size_t length>
    constexpr vec<T, length> operator/(const vec<T, length>& v, T t)
    {
        vec<T, length> output;
        for (std::size_t i = 0; i < length; i++)
        {
            output[i] = v[i] / t;
        }

        return output;
    }

    template <typename T, std::size_t length>
    constexpr vec<T, length> operator/(T t, const vec<T, length>& v)
    {
        vec<T, length> output;
        for (std::size_t i = 0; i < length; i++)
        {
            output[i] = t / v[i];
        }

        return output;
    }

    template <typename T, std::size_t length>
    constexpr vec<T, length> operator/(const vec<T, length>& v, const vec<T, length>& w)
    {
        vec<T, length> output;
        for (std::size_t i = 0; i < length; i++)
        {
            output[i] = v[i] / w[i];
        }

        return output;
    }

    // operator/=

    template <typename T, std::size_t length>
    constexpr vec<T, length>& operator/=(vec<T, length>& v, T t)
    {
        for (std::size_t i = 0; i < length; i++)
        {
            v[i] /= t;
        }

        return v;
    }

    template <typename T, std::size_t length>
    constexpr vec<T, length>& operator/=(vec<T, length>& v, const vec<T, length>& w)
    {
        for (std::size_t i = 0; i < length; i++)
        {
            v[i] /= w[i];
        }

        return v;
    }

    // operator==

    template <typename T, std::size_t length>
    constexpr bool operator==(const vec<T, length>& v, const vec<T, length>& w)
    {
        for (std::size_t i = 0; i < length; i++)
        {
            if (v[i] != w[i])
            {
                return false;
            }
        }

        return true;
    }

    template <typename T, std::size_t length>
    constexpr bool operator!=(const vec<T, length>& v, const vec<T, length>& w)
    {
        for (std::size_t i = 0; i < length; i++)
        {
            if (v[i] == w[i])
            {
                return true;
            }
        }

        return false;
    }

    template <typename T, std::size_t length>
    std::size_t hash(const vec<T, length>& v) noexcept
    {
        std::size_t output = std::hash<T>(v[0]);

        for (int i = 1; i < length; i++)
        {
            output = hash_combine(output, std::hash<T>(v[i]));
        }

        return output;
    }

    // A simple algorithm for combining two hash values,
    // algorithm from boost: http://www.boost.org/doc/libs/1_61_0/doc/html/hash/reference.html#boost.hash_combine
    constexpr inline std::size_t hash_combine(std::size_t hash1, std::size_t hash2)
    {
        return hash1 ^ (hash2 * 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
    }
}

namespace std
{
    template <typename T, std::size_t length>
    struct hash<maths::vec<T, length>>
    {
        std::size_t operator()(const maths::vec<T, length>& v) const noexcept
        {
            return maths::hash(v);
        }
    };
}

#endif // WINTER_VEC_OPERATIONS_H
