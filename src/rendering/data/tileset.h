#ifndef WINTER_TILESET_H
#define WINTER_TILESET_H

#include <resources/resource_handle.h>

struct Tileset
{
    ResourceHandle texture_handle;

    int tilewidth;
    int tileheight;
    int tilecount;
    int columns;
    int image_width;
    int image_height;

    Tileset(ResourceHandle texture_handle, int tilewidth, int tileheight,
        int tilecount, int columns, int image_width, int image_height)
        : texture_handle(texture_handle)
        , tilewidth(tilewidth)
        , tileheight(tileheight)
        , tilecount(tilecount)
        , columns(columns)
        , image_width(image_width)
        , image_height(image_height)
    {
    }
};

#endif // WINTER_TILESET_H
