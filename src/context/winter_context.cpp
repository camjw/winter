#include "winter_context.h"

WinterContext::WinterContext()
{
    resource_manager = std::make_shared<ResourceManager>();

    resource_manager->add_factory<Texture>(new TextureFactory());
    resource_manager->add_factory<Shader>(new ShaderFactory());
    resource_manager->add_factory<Material>(new MaterialFactory(resource_manager));
    resource_manager->add_factory<Mesh>(new MeshFactory());

    load_default_meshes();
    load_default_shaders();
}

void WinterContext::load_default_meshes()
{
    resource_manager->insert<Mesh>("square", Mesh::build_primitive(PrimitiveType::SQUARE));
}

void WinterContext::load_default_shaders()
{
    resource_manager->load<Shader>("pixel");
    resource_manager->load<Shader>("deferred");
}