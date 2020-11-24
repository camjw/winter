#ifndef WINTER_TILEMAP_LAYER_H
#define WINTER_TILEMAP_LAYER_H

#include <maths/grid.h>
#include <string>

struct TilemapLayer
{
    int id;
    std::string name;
    int width;
    int height;
    Grid<int> data;
};

#endif // WINTER_TILEMAP_LAYER_H
