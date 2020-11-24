#ifndef WINTER_TILEMAP_RENDERER_SERIALISER_H
#define WINTER_TILEMAP_RENDERER_SERIALISER_H

#include "component_serialiser.h"
#include <entity/entity.h>
#include <entity/tilemap_renderer.h>
#include <nlohmann/json.hpp>
#include <resources/resource_manager.h>
#include <rendering/data/tilemap.h>

class TilemapRendererSerialiser : public ComponentSerialiser<TilemapRenderer>
{
public:
    TilemapRendererSerialiser(std::shared_ptr<ResourceManager> resource_manager)
        : resource_manager(resource_manager)
    {
    }

    virtual nlohmann::json serialise(TilemapRenderer* component) override;
    virtual void deserialise(Entity* entity, nlohmann::json data) override;

private:
    std::shared_ptr<ResourceManager> resource_manager;
};

#endif //WINTER_TILEMAP_RENDERER_SERIALISER_H
