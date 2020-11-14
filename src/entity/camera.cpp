#include "camera.h"

const Matrix4x4 Camera::get_view_matrix(float aspect_ratio) const
{
    return Matrix4x4::identity();
}

const Matrix4x4 Camera::get_projection_matrix() const
{
    return Matrix4x4::identity();
}

const float3 Camera::get_clear_colour()
{
    return float3();
}
