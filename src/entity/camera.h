#ifndef WINTER_CAMERA_H
#define WINTER_CAMERA_H

#include "component.h"
#include <maths/colour.h>
#include <maths/maths.h>

class Camera : public Component
{
public:
    Camera(Entity* entity);

    const float4x4 get_projection_matrix(float aspect_ratio) const;
    const float4x4 get_view_matrix() const;

    colour clear_colour = colour::black();
    float orthographic_size = 50.0f;
};

#endif //WINTER_CAMERA_H
