#ifndef WINTER_MATERIAL_H
#define WINTER_MATERIAL_H

#include "shader.h"
#include "texture.h"
#include <maths/float3.h>

using MaterialID = uint32_t;
const MaterialID INVALID_MATERIAL = UINT32_MAX;

enum RenderMode
{
    OPAQUE,
    TRANSPARENT,
};

struct MaterialComponent
{
    MaterialID material_id = INVALID_MATERIAL;
    RenderMode render_mode = OPAQUE;

    explicit MaterialComponent() = default;

    MaterialComponent(MaterialID material_id, RenderMode render_mode)
        : material_id(material_id)
        , render_mode(render_mode)
    {
    }
};

struct Material
{
    float3 colour;

    TextureID texture = INVALID_TEXTURE;
    TextureProperties texture_properties = DEFAULT_TEXTURE_PROPERTIES;
    bool use_texture = true;

    ShaderID shader;
};

#endif // WINTER_MATERIAL_H
