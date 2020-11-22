#ifndef WINTER_MATERIAL_H
#define WINTER_MATERIAL_H

#include "shader.h"
#include "texture.h"
#include <maths/colour.h>
#include <maths/float3.h>
#include <resources/resource_handle.h>

enum RenderMode
{
    OPAQUE,
    TRANSPARENT,
};

inline RenderMode render_mode_from_string(const std::string& render_mode)
{
    std::string render_mode_lower = render_mode;
    std::transform(render_mode_lower.begin(), render_mode_lower.end(), render_mode_lower.begin(), ::tolower);
    if (render_mode_lower == "transparent")
    {
        return RenderMode::TRANSPARENT;
    }

    return RenderMode::OPAQUE;
}


struct Material
{
    colour colour;

    ResourceHandle texture = ResourceHandle::invalid_handle<Texture>();
    ResourceHandle shader = ResourceHandle::invalid_handle<Shader>();

    bool use_texture = true;
    RenderMode render_mode = OPAQUE;
};

#endif // WINTER_MATERIAL_H
