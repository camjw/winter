#ifndef WINTER_TRANSFORM_H
#define WINTER_TRANSFORM_H

#include <maths/float3.h>
#include <maths/quaternion.h>

struct Transform
{
    float3 position = float3::zero();
    quaternion rotation = quaternion::identity();
    float3 scale = float3::one();

    Matrix4x4 get_model_matrix()
    {
        Matrix4x4 model_matrix = Matrix4x4::diagonal(1.0f);

        model_matrix = Matrix4x4::scale(scale) * model_matrix;
        model_matrix = Matrix4x4::rotation(rotation) * model_matrix;
        model_matrix = Matrix4x4::translate(position) * model_matrix;
        return model_matrix;
    }

    static Transform identity()
    {
        return Transform();
    }
};

REGISTER_COMPONENT(Transform, Transform)

#endif // WINTER_TRANSFORM_H
