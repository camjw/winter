#ifndef WINTER_TILEMAP_FACTORY_H
#define WINTER_TILEMAP_FACTORY_H

#include "pugixml.hpp"
#include "resource_manager.h"
#include <iostream>
#include <rendering/data/tilemap.h>
#include <rendering/data/tilemap_layer.h>
#include <string>
#include <rendering/data/tileset.h>
#include <utils/opengl_helpers.h>
#include <vector>

class TilemapFactory : public ResourceFactory<Tilemap>
{
public:
    explicit TilemapFactory(std::shared_ptr<ResourceManager> resource_manager)
        : ResourceFactory("assets/tilemaps", ".tmx")
        , resource_manager(resource_manager) {};

protected:
    virtual std::shared_ptr<Tilemap> build(const std::string& name) override;

private:
    std::shared_ptr<ResourceManager> resource_manager;
    std::string get_tileset_name(const std::string& relative_path) const;
    TilemapLayer build_tilemap_layer(pugi::xml_named_node_iterator iterator) const;
};

#endif // WINTER_TILEMAP_FACTORY_H
