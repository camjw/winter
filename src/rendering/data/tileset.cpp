#include "tileset.h"

// TODO: if tile_type is 0 then the tile is empty. Maybe use boolean flag?
float3x3 calculate_tile_transform(int tile_type, Tileset tileset)
{
    int tile_index = tile_type == 0 ? 0 : tile_type - 1;
    int column_index = tile_index % tileset.columns;
    int row_index = tile_index / tileset.columns;

    int tileset_rows = tileset.tilecount / tileset.columns;

    float texture_tile_column_side_length = 1.0f / tileset.columns;
    float texture_tile_row_side_length = 1.0f / tileset_rows;

    float3x3 output = float3x3::diagonal(float3(texture_tile_column_side_length, texture_tile_row_side_length, 1.0f));

    // (0, 0) -> bottom left
    // (1, 0) -> bottom right
    // (0, 1) -> top left
    // (1, 1) -> top right
    float2 bottom_left_texture_coord = float2(column_index * texture_tile_column_side_length, (tileset_rows - row_index - 1) * texture_tile_row_side_length);

    output.z[0] = bottom_left_texture_coord.x;
    output.z[1] = bottom_left_texture_coord.y;

    if (tile_type != 0)
    {
        printf("break\n");
    }

    return output;
}