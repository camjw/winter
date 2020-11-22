#ifndef WINTER_TILEMAP_H
#define WINTER_TILEMAP_H

#include <resources/resource_handle.h>

struct Tilemap
{
    Tilemap(ResourceHandle texture): texture(texture) {};

    ResourceHandle texture;
};

#endif //WINTER_TILEMAP_H
