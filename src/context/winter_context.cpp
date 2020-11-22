#include "winter_context.h"
#include <rendering/data/tilemap.h>
#include <rendering/data/tileset.h>
#include <resources/tilemap_factory.h>
#include <resources/tileset_factory.h>

WinterContext::WinterContext()
{
    resource_manager = std::make_shared<ResourceManager>();

    resource_manager->add_factory<Texture>(new TextureFactory());
    resource_manager->add_factory<Shader>(new ShaderFactory());
    resource_manager->add_factory<Material>(new MaterialFactory(resource_manager));
    resource_manager->add_factory<Mesh>(new MeshFactory());
    resource_manager->add_factory<Tilemap>(new TilemapFactory(resource_manager));
    resource_manager->add_factory<Tileset>(new TilesetFactory(resource_manager));

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