#include "tilemap_renderer_serialiser.h"

nlohmann::json TilemapRendererSerialiser::serialise(TilemapRenderer* component)
{
    return nlohmann::json();
}

void TilemapRendererSerialiser::deserialise(Entity* entity, nlohmann::json data)
{
    std::shared_ptr<TilemapRenderer> tilemap_renderer = entity->add_component<TilemapRenderer>();

    ResourceHandle tilemap_handle = resource_manager->load<Tilemap>(data["tilemap"]);
    tilemap_renderer->tilemap = tilemap_handle;
}
