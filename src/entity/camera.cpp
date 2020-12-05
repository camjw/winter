#include "camera.h"
#include "entity.h"

Camera::Camera(Entity* entity): Component(entity)
{
}

const float4x4 Camera::get_view_matrix() const
{
    return maths::look_at_2d(transform()->get_position());
}

const float4x4 Camera::get_projection_matrix(float aspect_ratio) const
{
    return maths::orthographic_projection(orthographic_size, aspect_ratio);
}