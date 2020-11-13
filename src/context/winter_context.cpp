#include "winter_context.h"

WinterContext::WinterContext()
{
    mesh_repository = std::make_shared<MeshRepository>();
    texture_repository = std::make_shared<TextureRepository>();
    material_repository = std::make_shared<MaterialRepository>();
    shader_repository = std::make_shared<ShaderRepository>();
}