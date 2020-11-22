#ifndef WINTER_TILESET_FACTORY_H
#define WINTER_TILESET_FACTORY_H

#include <rendering/data/tileset.h>
#include <resources/resource_manager.h>

class TilesetFactory : public ResourceFactory<Tileset>
{
public:
    TilesetFactory(std::shared_ptr<ResourceManager> resource_manager)
        : ResourceFactory("assets/tilesets", ".tsx")
        , resource_manager(resource_manager)
    {
    }

    virtual std::shared_ptr<Tileset> build(const std::string& name) override
    {
        pugi::xml_document tileset_xml;
        pugi::xml_parse_result result = tileset_xml.load_file(get_full_path_with_extension(name).c_str());
        if (!result)
        {
            return nullptr;
        }

        std::string texture_relative_path = tileset_xml
                                                .child("tileset")
                                                .child("image")
                                                .attribute("source")
                                                .as_string();
        std::string texture_name = get_texture_name(texture_relative_path);

        ResourceHandle texture_handle = resource_manager->load<Texture>(texture_name);

        int tilewidth = tileset_xml.child("tileset").attribute("tilewidth").as_int();
        int tileheight = tileset_xml.child("tileset").attribute("tileheight").as_int();
        int tilecount = tileset_xml.child("tileset").attribute("tilecount").as_int();
        int columns = tileset_xml.child("tileset").attribute("columns").as_int();
        int image_width = tileset_xml.child("tileset").child("image").attribute("width").as_int();
        int image_height = tileset_xml.child("tileset").child("image").attribute("height").as_int();

        return std::make_shared<Tileset>(
            texture_handle,
            tilewidth,
            tileheight,
            tilecount,
            columns,
            image_width,
            image_height);
    }

private:
    std::shared_ptr<ResourceManager> resource_manager;

    inline std::string get_texture_name(const std::string& relative_filepath) const
    {
        return relative_filepath.substr(relative_filepath.find_last_of("/\\") + 1);
    }
};

#endif // WINTER_TILESET_FACTORY_H
