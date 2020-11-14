#ifndef WINTER_RENDER_QUEUE_H
#define WINTER_RENDER_QUEUE_H

#include "material.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include <maths/matrix4x4.h>

struct RenderCommand
{
    MeshID mesh_id;

    ShaderID shader_id;

    TextureID texture_id = 0;

    MaterialID material_id;

    Matrix4x4 transform;
};

class RenderQueue
{
public:
    inline void push_back(const RenderCommand render_command)
    {
        commands.push_back(render_command);
    }

    inline void clear()
    {
        commands.clear();
    }

    std::vector<RenderCommand> commands;
};

#endif //DEMO_RENDER_QUEUE_H
