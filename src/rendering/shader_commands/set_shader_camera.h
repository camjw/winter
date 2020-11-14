#ifndef WINTER_SET_SHADER_CAMERA_H
#define WINTER_SET_SHADER_CAMERA_H

#include <constants/shader_constants.h>
#include <maths/float3.h>
#include <rendering/shader.h>
#include <templates/action.h>

class SetShaderCamera
{
public:
    SetShaderCamera(Matrix4x4 view)
        : view(view) {};

    inline void operator()(Shader* shader)
    {
        shader->bind();
        shader->set_mat4(WINTER_CONSTANTS_VIEW, view);
    }

private:
    Matrix4x4 view;
};

#endif // WINTER_SET_SHADER_CAMERA_H
