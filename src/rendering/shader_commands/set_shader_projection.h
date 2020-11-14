#ifndef WINTER_SET_SHADER_PROJECTION_H
#define WINTER_SET_SHADER_PROJECTION_H

#include <constants/shader_constants.h>
#include <rendering/shader.h>
#include <templates/action.h>

class SetShaderProjection
{
public:
    SetShaderProjection(const Matrix4x4& projection)
        : projection(projection) {};

    inline void operator()(Shader* shader)
    {
        shader->bind();
        shader->set_mat4(WINTER_CONSTANTS_PROJECTION, projection);
    }

private:
    Matrix4x4 projection;
};

#endif // WINTER_SET_SHADER_PROJECTION_H
