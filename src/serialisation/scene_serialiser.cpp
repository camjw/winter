#include "scene_serialiser.h"
#include <constants/folder_constants.h>
#include <rendering/data/material.h>
#include <rendering/data/shader.h>
#include <rendering/data/texture.h>
#include <rendering/data/tilemap.h>

void SceneSerialiser::load_scene(const std::string& scene_name, Scene* scene)
{
    nlohmann::json scene_data;
    std::ifstream scene_stream(get_full_path(scene_name));
    scene_stream >> scene_data;

    ResourcesLoadInfo resources_load_info = load_resources(scene_data);
    int num_loaded_entities = load_entities(scene, scene_data, scene->get_root()->transform);
}

int SceneSerialiser::load_entities(Scene* scene, const nlohmann::json& scene_data, std::shared_ptr<Transform> root_transform)
{
    std::vector<nlohmann::json> entity_data = scene_data["entities"];

    for (int i = 0; i < entity_data.size(); i++)
    {
        load_entity(scene, entity_data[i], root_transform);
    }

    return entity_data.size();
}

std::shared_ptr<Entity> SceneSerialiser::load_entity(Scene* scene, const nlohmann::json& entity_data, std::shared_ptr<Transform> parent_transform)
{
    std::string entity_name = entity_data["name"];
    std::shared_ptr<Entity> entity = scene->get_entity_manager()->create_entity(entity_name, parent_transform);

    std::vector<nlohmann::json> component_data = entity_data["components"];
    for (int i = 0; i < component_data.size(); i++)
    {
        get_component_serialiser(component_data[i]["type"])->deserialise(entity.get(), component_data[i]);
    }

    std::shared_ptr<Transform> entity_transform = entity->transform;
    std::vector<nlohmann::json> children_data = entity_data["children"];

    for (int i = 0; i < children_data.size(); i++)
    {
        std::shared_ptr<Entity> child_entity = load_entity(scene, children_data[i], entity_transform);
        child_entity->transform->set_parent(entity_transform);
    }

    return entity;
}

ResourcesLoadInfo SceneSerialiser::load_resources(nlohmann::json scene_data)
{
    nlohmann::json resources_data = scene_data["resources"];
    std::vector<std::string> material_data = resources_data["materials"];
    std::vector<std::string> shader_data = resources_data["shaders"];
    std::vector<std::string> texture_data = resources_data["textures"];
    std::vector<std::string> tilemap_data = resources_data["tilemaps"];

    for (int i = 0; i < material_data.size(); i++)
    {
        resource_manager->load<Material>(material_data[i]);
    }

    for (int i = 0; i < shader_data.size(); i++)
    {
        resource_manager->load<Shader>(shader_data[i]);
    }

    for (int i = 0; i < texture_data.size(); i++)
    {
        resource_manager->load<Texture>(texture_data[i]);
    }

    for (int i = 0; i < tilemap_data.size(); i++)
    {
        resource_manager->load<Tilemap>(tilemap_data[i]);
    }

    return ResourcesLoadInfo {
        .num_loaded_materials = material_data.size(),
        .num_loaded_shaders = shader_data.size(),
        .num_loaded_textures = texture_data.size(),
        .num_loaded_tilemaps = tilemap_data.size(),
    };
}

nlohmann::json SceneSerialiser::save_scene(Scene* scene) const
{
    return nlohmann::json();
}

std::string SceneSerialiser::get_full_path(const std::string& scene_name) const
{
    return WINTER_ROOT + "/" + SCENE_DIRECTORY + "/" + scene_name + SCENE_FILETYPE;
}
