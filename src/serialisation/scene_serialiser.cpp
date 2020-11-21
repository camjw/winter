#include "scene_serialiser.h"
#include <constants/folder_constants.h>
#include <rendering/mesh.h>
#include <rendering/shader.h>
#include <rendering/texture.h>
#include <iostream>

void SceneSerialiser::load_scene(const std::string& scene_name, Scene* scene)
{
    nlohmann::json scene_data;
    std::ifstream scene_stream(get_full_path(scene_name));
    scene_stream >> scene_data;

    load_resources(scene_data);
    load_entities(scene, scene_data, scene->get_root()->transform);
}

void SceneSerialiser::load_entities(Scene* scene, const nlohmann::json& scene_data, std::shared_ptr<Transform> root_transform)
{
    std::vector<nlohmann::json> entity_data = scene_data["entities"];

    for (int i = 0; i < entity_data.size(); i++)
    {
        load_entity(scene, entity_data[i], root_transform);
    }
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

void SceneSerialiser::load_resources(nlohmann::json scene_data)
{
    nlohmann::json resources_data = scene_data["resources"];
    std::vector<std::string> shader_data = resources_data["shaders"];
    std::vector<std::string> mesh_data = resources_data["meshes"];
    std::vector<std::string> texture_data = resources_data["textures"];

    for (int i = 0; i < mesh_data.size(); i++)
    {
        resource_manager->load<Mesh>(mesh_data[i]);
    }

    for (int i = 0; i < texture_data.size(); i++)
    {
        resource_manager->load<Texture>(texture_data[i]);
    }

    for (int i = 0; i < shader_data.size(); i++)
    {
        resource_manager->load<Shader>(shader_data[i]);
    }
}

nlohmann::json SceneSerialiser::save_scene(Scene* scene) const
{
    return nlohmann::json();
}

std::string SceneSerialiser::get_full_path(const std::string& scene_name) const
{
    return WINTER_ROOT + "/" + SCENE_DIRECTORY + "/" + scene_name + SCENE_FILETYPE;
}
