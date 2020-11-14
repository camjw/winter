#ifndef WINTER_CAMERA_H
#define WINTER_CAMERA_H

#include "component.h"
#include <maths/matrix4x4.h>

class Camera : public Component
{
public:
    const Matrix4x4 get_projection_matrix() const;
    const Matrix4x4 get_view_matrix(float aspect_ratio) const;
    const float3 get_clear_colour();
};

#endif //WINTER_CAMERA_H
