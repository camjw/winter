#ifndef WINTER_CAMERA_H
#define WINTER_CAMERA_H

#include "component.h"
#include <maths/matrix4x4.h>

class Camera : public Component
{
public:
    Camera(Entity* entity): Component(entity) {}

    const Matrix4x4 get_projection_matrix() const;
    const Matrix4x4 get_view_matrix(float aspect_ratio) const;

    float3 clear_colour = float3(0.0f);
};

#endif //WINTER_CAMERA_H
