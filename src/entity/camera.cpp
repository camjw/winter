#include "camera.h"
#include "entity.h"

Camera::Camera(Entity* entity): Component(entity)
{
}

const Matrix4x4 Camera::get_view_matrix(float aspect_ratio) const
{
    return Matrix4x4::identity();
}

const Matrix4x4 Camera::get_projection_matrix() const
{
    return Matrix4x4::identity();
}

void Camera::set_clear_colour(float3 clear_colour)
{
    _clear_colour = clear_colour;
}
