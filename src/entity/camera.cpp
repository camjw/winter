#include "camera.h"
#include "entity.h"

Camera::Camera(Entity* entity)
    : Component(entity)
{
}

const float4x4 Camera::get_view_matrix() const
{
    return maths::look_at_2d(transform()->position());
}

const float4x4 Camera::get_projection_matrix(float aspect_ratio) const
{
    return maths::orthographic_projection(orthographic_size, aspect_ratio);
}

void Camera::update(const Time& time, const Input* input)
{
    if (input->get_key(Key::Left))
    {
        printf("Left pressed\n");
        transform()->position() += track_speed * float2(-1, 0) * time.delta_time;
    }

    if (input->get_key(Key::Right))
    {
        printf("Right pressed\n");
        transform()->position() += track_speed * float2(1, 0) * time.delta_time;
    }

    if (input->get_key(Key::Up))
    {
        printf("Up pressed\n");
        transform()->position() += track_speed * float2(0, 1) * time.delta_time;
    }

    if (input->get_key(Key::Down))
    {
        printf("Down pressed\n");
        transform()->position() += track_speed * float2(0, -1) * time.delta_time;
    }
}
