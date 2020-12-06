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

        output.w[0] = t.x;
        output.w[1] = t.y;
        output.w[2] = t.z;

        return output;
    }

    static float4x4 rotation(quaternion q)
    {
        float4x4 output = float4x4::identity();

        output[0][0] = 1 - 2 * (q.y * q.y + q.z * q.z);
        output[1][0] = 2 * (q.x * q.y - q.z * q.w);
        output[2][0] = 2 * (q.x * q.z + q.y * q.w);

        output[0][1] = 2 * (q.x * q.y + q.z * q.w);
        output[1][1] = 1 - 2 * (q.x * q.x + q.z * q.z);
        output[2][1] = 2 * (q.y * q.z - q.x * q.w);

        output[0][2] = 2 * (q.x * q.z - q.y * q.w);
        output[1][2] = 2 * (q.y * q.z + q.x * q.w);
        output[2][2] = 1 - 2 * (q.x * q.x + q.y * q.y);

        return output;
    }

    static float4x4 look_at_2d(const float2& position)
    {
        float4x4 output = float4x4::zero();

        output[0][0] = 1;
        output[1][0] = 0;
        output[2][0] = 0;
        output[3][0] = -position.x;

        output[0][1] = 0;
        output[1][1] = 1;
        output[2][1] = 0;
        output[3][1] = -position.y;

        output[0][2] = 0;
        output[1][2] = 0;
        output[2][2] = 1;
        output[3][2] = -64;

        output[0][3] = 0;
        output[1][3] = 0;
        output[2][3] = 0;
        output[3][3] = 1;

        return output;
    }

    // Aspect ratio is width / height
    static float4x4 orthographic_projection(float orthographic_size, float aspect_ratio)
    {
        float4x4 output = float4x4::zero();

        output[0][0] = 1.0f / (aspect_ratio * orthographic_size);

        output[1][1] = 1.0f / orthographic_size;

        output[2][2] = 1.0f / 255;

        output[3][0] = 0;
        output[3][1] = 0;
        output[3][2] = -1.0f / 255;
        output[3][3] = 1;

        return output;
    }
}

#endif
