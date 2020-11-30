#ifndef WINTER_MATHS_MATHS_HPP
#define WINTER_MATHS_MATHS_HPP

#include <maths/matrix.h>
#include <maths/matrix_operations.h>
#include <maths/quaternion.h>
#include <maths/vec.h>
#include <maths/vec_operations.h>

namespace maths
{
    static float3 multiply(quaternion q, float3 v)
    {
        quaternion c = q.inverse() * quaternion(0, v.x, v.y, v.z) * q;
        return float3(c.x, c.y, c.z);
    }

    static float mod(float value, float modulus)
    {
        return value - (modulus * int(value / modulus));
    }

    static float min(float first, float second)
    {
        if (first < second)
        {
            return first;
        }

        return second;
    }

    static float max(float first, float second)
    {
        if (first < second)
        {
            return second;
        }

        return first;
    }

    static float clamp(float value, float min, float max)
    {
        if (value < min)
        {
            return min;
        }

        if (value > max)
        {
            return max;
        }

        return value;
    }

    static float4x4 scale(float s)
    {
        return float4x4::diagonal(s);
    }

    static float4x4 scale(float3 s)
    {
        float4x4 output = float4x4::identity();

        output.x[0] = s.x;
        output.y[1] = s.y;
        output.z[2] = s.z;

        return output;
    }

    static float4x4 translation(float3 t)
    {
        float4x4 output = float4x4::identity();

        output.x[3] = t.x;
        output.y[3] = t.y;
        output.z[3] = t.z;

        return output;
    }

    static float4x4 rotation(quaternion q)
    {
        float4x4 output = float4x4::identity();

        output.x[0] = 1 - 2 * (q.y * q.y + q.z * q.z);
        output.x[1] = 2 * (q.x * q.y - q.z * q.w);
        output.x[2] = 2 * (q.x * q.z + q.y * q.w);

        output.y[0] = 2 * (q.x * q.y + q.z * q.w);
        output.y[1] = 1 - 2 * (q.x * q.x + q.z * q.z);
        output.y[2] = 2 * (q.y * q.z - q.x * q.w);

        output.z[0] = 2 * (q.x * q.z - q.y * q.w);
        output.z[0] = 2 * (q.y * q.z + q.x * q.w);
        output.z[2] = 1 - 2 * (q.x * q.x + q.y * q.y);

        return output;
    }

}

#endif
