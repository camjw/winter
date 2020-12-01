#ifndef WINTER_TILEMAP_LAYER_H
#define WINTER_TILEMAP_LAYER_H

#include <maths/containers/grid.h>
#include <string>
#include <vector>

struct TilemapLayer
{
    int id;
    std::string name;
    int width;
    int height;
    std::vector<std::vector<int>> data;
};

#endif // WINTER_TILEMAP_LAYER_H
