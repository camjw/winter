#ifndef WINTER_CAMERA_H
#define WINTER_CAMERA_H

#include "component.h"
#include <maths/colour.h>
#include <maths/matrix4x4.h>

class Camera : public Component
{
public:
    Camera(Entity* entity);

    const Matrix4x4 get_projection_matrix() const;
    const Matrix4x4 get_view_matrix(float aspect_ratio) const;

    void set_clear_colour(colour clear_colour);

    const colour clear_colour() const
    {
        return _clear_colour;
    }

private:
    colour _clear_colour = colour::black();
};

#endif //WINTER_CAMERA_H
