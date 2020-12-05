#include "tileset.h"

float3x3 calculate_tile_transform(int tile_type, Tileset tileset)
{
    int column_index = tile_type % tileset.columns;
    int row_index = tile_type / tileset.columns;

    int num_rows = tileset.tilecount / tileset.columns;

    float texture_tile_side_length = 1.0f / tileset.columns;

    float3x3 output = float3x3::diagonal(float3(texture_tile_side_length, texture_tile_side_length, 1.0f));

    float2 top_left_texture_coord = float2(column_index * texture_tile_side_length, row_index * texture_tile_side_length);

    output.z[0] = top_left_texture_coord.x;
    output.z[1] = top_left_texture_coord.y;

    return output;
}