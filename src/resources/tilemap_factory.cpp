#include "tilemap_factory.h"
#include <maths/containers/grid.h>
#include <rendering/data/material.h>
#include <sstream>
#include <string>

std::shared_ptr<Tilemap> TilemapFactory::build(const std::string& name)
{
    pugi::xml_document tilemap_xml;
    pugi::xml_parse_result result = tilemap_xml.load_file(get_full_path_with_extension(name).c_str());
    if (!result)
    {
        return nullptr;
    }

    std::string tileset_relative_path = tilemap_xml.child("map").child("tileset").attribute("source").as_string();
    std::string tileset_name = get_tileset_name(tileset_relative_path);

    ResourceHandle tileset_texture_handle = resource_manager->load<Tileset>(tileset_name);
    Material tileset_material = Material {
        .texture = tileset_texture_handle,
        .shader = resource_manager->load<Shader>("tilemap"),
    };

    ResourceHandle tileset_material_handle = resource_manager->insert<Material>(tileset_name + "_material", std::move(tileset_material));

    glCheckError();

    pugi::xml_object_range<pugi::xml_named_node_iterator> layers = tilemap_xml.child("map").children("layer");
    std::vector<TilemapLayer> tilemap_layers;

    for (pugi::xml_named_node_iterator layer = layers.begin(); layer != layers.end(); ++layer)
    {
        tilemap_layers.push_back(build_tilemap_layer(layer));
    }

    bool infinite = tilemap_xml.child("map").attribute("infinite").as_bool();
    Tilemap tilemap = Tilemap {
        .material = tileset_material_handle,
        .layers = tilemap_layers,
        .infinite = infinite
    };

    return std::make_shared<Tilemap>(tilemap);
}

std::string TilemapFactory::get_tileset_name(const std::string& relative_path) const
{
    std::string base_filename = relative_path.substr(relative_path.find_last_of("/\\") + 1);
    std::string::size_type const p(base_filename.find_last_of('.'));
    return base_filename.substr(0, p);
}

TilemapLayer TilemapFactory::build_tilemap_layer(pugi::xml_named_node_iterator layer_data) const
{
    int id = layer_data->attribute("id").as_int();
    std::string name = layer_data->attribute("name").as_string();
    int width = layer_data->attribute("width").as_int();
    int height = layer_data->attribute("height").as_int();

    auto  = layer_data->children();
    std::string data_string = layer_data->child("data").value();

    std::vector<std::vector<int>> data(height, std::vector<int>());

    std::stringstream data_stream(data_string);
    std::string next_tile;
    int counter = 0;
    while (std::getline(data_stream, next_tile, ','))
    {
        int tile_data = atoi(next_tile.c_str());
        data[counter / width].push_back(tile_data);
        counter++;
    }

    return TilemapLayer {
        .id = id,
        .name = name,
        .width = width,
        .height = height,
        .data = data,
    };
}
