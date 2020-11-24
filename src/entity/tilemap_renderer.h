#ifndef WINTER_TILEMAP_RENDERER_H
#define WINTER_TILEMAP_RENDERER_H

#include "component.h"
#include "entity.h"
#include <rendering/data/tilemap.h>

class TilemapRenderer : public Component
{
public:
    TilemapRenderer(Entity* entity)
        : Component(entity) {};

    ResourceHandle tilemap = ResourceHandle::invalid_handle<Tilemap>();
};

#endif // WINTER_TILEMAP_RENDERER_H
