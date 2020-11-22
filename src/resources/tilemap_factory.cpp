#include "tilemap_factory.h"
#include <rendering/data/tileset.h>
#include <utils/opengl_helpers.h>

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
    printf("tileset name: %s\n", tileset_name.c_str());

    ResourceHandle tileset_handle = resource_manager->load<Tileset>(tileset_name);
    glCheckError();
    return nullptr;
}

std::string TilemapFactory::get_tileset_name(const std::string& relative_path) const
{
    std::string base_filename = relative_path.substr(relative_path.find_last_of("/\\") + 1);
    std::string::size_type const p(base_filename.find_last_of('.'));
    return base_filename.substr(0, p);
}