#ifndef WINTER_TILEMAP_H
#define WINTER_TILEMAP_H

#include "tilemap_layer.h"
#include <resources/resource_handle.h>
#include <vector>

struct Tilemap
{
    ResourceHandle material;
    std::vector<TilemapLayer> layers;
    bool infinite;
};

#endif //WINTER_TILEMAP_H
