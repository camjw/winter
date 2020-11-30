#ifndef WINTER_RENDER_QUEUE_H
#define WINTER_RENDER_QUEUE_H

#include "rendering/data/material.h"
#include "rendering/data/mesh.h"
#include "rendering/data/shader.h"
#include "rendering/data/texture.h"
#include <maths/maths.h>

struct RenderCommand
{
    ResourceHandle mesh;
    ResourceHandle material;

    float4x4 transform;
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
