#ifndef WINTER_MATRIX4X4_H
#define WINTER_MATRIX4X4_H

#include "quaternion.h"
#include "float4.h"
#include "float3.h"

struct Matrix4x4
{
    explicit Matrix4x4()
    {
        values = new float[16];
    }

    ~Matrix4x4()
    {
        delete (values);
    }

    float* values;

    Matrix4x4 static identity()
    {
        return diagonal(1.0f);
    }

    Matrix4x4 static diagonal(float diagonal_value)
    {
        Matrix4x4 output;
        output.values[0] = diagonal_value;
        output.values[5] = diagonal_value;
        output.values[10] = diagonal_value;
        output.values[15] = diagonal_value;
        return output;
    }

    Matrix4x4 static scale(float3 scale)
    {
        Matrix4x4 output;
        output.values[0] = scale.x;
        output.values[5] = scale.y;
        output.values[10] = scale.z;
        output.values[15] = 1.0f;
        return output;
    }

    Matrix4x4 static rotation(quaternion rotation)
    {
        Matrix4x4 output;
        float w = rotation.w;
        float x = rotation.x;
        float y = rotation.y;
        float z = rotation.z;

        output.values[0] = 1 - 2 * (y * y + z * z);
        output.values[1] = 2 * (x * y - z * w);
        output.values[2] = 2 * (x * z + y * w);

        output.values[4] = 2 * (x * y + z * w);
        output.values[5] = 1 - 2 * (x * x + z * z);
        output.values[6] = 2 * (y * z - x * w);

        output.values[8] = 2 * (x * z - y * w);
        output.values[9] = 2 * (y * z + x * w);
        output.values[10] = 1 - 2 * (x * x + y * y);

        return output;
    }

    Matrix4x4 static translate(float3 translation)
    {
        Matrix4x4 output;
        output.values[3] = translation.x;
        output.values[7] = translation.y;
        output.values[11] = translation.z;
        output.values[15] = 1.0f;
        return output;
    }

    const float4 operator[](const int index) const
    {
        switch (index)
        {
        case 0:
            return float4(&values[0]);
        case 1:
            return float4(&values[4]);
        case 2:
            return float4(&values[8]);
        default:
            return float4(&values[12]);
        }
    }

    inline float& get(int i, int j)
    {
        return values[4 * i + j];
    }

    Matrix4x4 operator*(const Matrix4x4& right) const
    {
        Matrix4x4* output = new Matrix4x4();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                float matrix_entry = 0.0f;
                for (int k = 0; k < 4; k++)
                {
                    matrix_entry += (this->operator[](i)[k] * right[k][j]);
                }

                output->get(i, j) = matrix_entry;
            }
        }

        return *output;
    }

    operator float*() { return reinterpret_cast<float*>(this); }

    operator const float*() const { return reinterpret_cast<const float*>(this); }
};

#endif // WINTER_MATRIX4X4_H
