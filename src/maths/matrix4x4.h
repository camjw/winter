#ifndef WINTER_MATRIX4X4_H
#define WINTER_MATRIX4X4_H

#include "float3.h"
#include "float4.h"
#include "quaternion.h"

struct Matrix4x4
{
    float m00 = 0.0f, m01 = 0.0f, m02 = 0.0f, m03 = 0.0f;
    float m10 = 0.0f, m11 = 0.0f, m12 = 0.0f, m13 = 0.0f;
    float m20 = 0.0f, m21 = 0.0f, m22 = 0.0f, m23 = 0.0f;
    float m30 = 0.0f, m31 = 0.0f, m32 = 0.0f, m33 = 0.0f;

    Matrix4x4 static identity()
    {
        return diagonal(1.0f);
    }

    Matrix4x4 static diagonal(float diagonal_value)
    {
        Matrix4x4 output;
        output.m00 = diagonal_value;
        output.m11 = diagonal_value;
        output.m22 = diagonal_value;
        output.m33 = diagonal_value;
        return output;
    }

    Matrix4x4 static scale(float3 scale)
    {
        Matrix4x4 output;
        output.m00 = scale.x;
        output.m11 = scale.y;
        output.m22 = scale.z;
        output.m33 = 1.0f;
        return output;
    }

    Matrix4x4 static rotation(quaternion rotation)
    {
        Matrix4x4 output;
        float w = rotation.w;
        float x = rotation.x;
        float y = rotation.y;
        float z = rotation.z;

        output.m00 = 1 - 2 * (y * y + z * z);
        output.m01 = 2 * (x * y - z * w);
        output.m02 = 2 * (x * z + y * w);

        output.m10 = 2 * (x * y + z * w);
        output.m11 = 1 - 2 * (x * x + z * z);
        output.m12 = 2 * (y * z - x * w);

        output.m20 = 2 * (x * z - y * w);
        output.m21 = 2 * (y * z + x * w);
        output.m22 = 1 - 2 * (x * x + y * y);

        return output;
    }

    Matrix4x4 static translate(float3 translation)
    {
        Matrix4x4 output;
        output.m03 = translation.x;
        output.m13 = translation.y;
        output.m23 = translation.z;
        output.m33 = 1.0f;
        return output;
    }

    const float4 operator[](const int index) const
    {
        switch (index)
        {
        case 0:
            return float4(m00, m01, m02, m03);
        case 1:
            return float4(m10, m11, m12, m13);
        case 2:
            return float4(m20, m21, m22, m23);
        default:
            return float4(m30, m31, m32, m33);
        }
    }

    inline float& get(int i, int j)
    {
        int index = 4 * i + j;
        switch (index)
        {
        case 0:
            return m00;
        case 1:
            return m01;
        case 2:
            return m02;
        case 3:
            return m03;
        case 4:
            return m10;
        case 5:
            return m11;
        case 6:
            return m12;
        case 7:
            return m13;
        case 8:
            return m20;
        case 9:
            return m21;
        case 10:
            return m22;
        case 11:
            return m23;
        case 12:
            return m30;
        case 13:
            return m31;
        case 14:
            return m32;
        default:
            return m33;
        }
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
