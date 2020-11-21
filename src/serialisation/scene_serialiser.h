#ifndef WINTER_SCENE_SERIALISER_H
#define WINTER_SCENE_SERIALISER_H

#include "camera_serialiser.h"
#include "component_serialiser.h"
#include "transform_serialiser.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <resources/resource_manager.h>
#include <scene/scene.h>
#include <string>

class SceneSerialiser
{
public:
    SceneSerialiser(const std::string& scene_directory, std::shared_ptr<ResourceManager> resource_manager)
        : SCENE_DIRECTORY(scene_directory)
        , resource_manager(resource_manager)
    {
        register_component_serialiser<Transform>(new TransformSerialiser());
        register_component_serialiser<Camera>(new CameraSerialiser());
    }

    void load_scene(const std::string& scene_name, Scene* scene);
    nlohmann::json save_scene(Scene* scene) const;

private:
    template <typename T>
    bool register_component_serialiser(ComponentSerialiser<T>* component_serialiser)
    {
        std::type_index factory_type_index = std::type_index(typeid(T));
        auto existing_serialiser = component_serialisers.find(factory_type_index);

        if (existing_serialiser != component_serialisers.end())
        {
            return false;
        }

        JSONComponentSerialiser* abstract_serialiser = static_cast<JSONComponentSerialiser*>(component_serialiser);
        component_serialisers[std::type_index(typeid(T))] = abstract_serialiser;
        return true;
    }

    JSONComponentSerialiser* get_component_serialiser(const std::string& component_type) const
    {
        std::string component_type_lowercase = component_type;
        std::transform(component_type_lowercase.begin(), component_type_lowercase.end(), component_type_lowercase.begin(), ::tolower);

        if (component_type_lowercase == "transform")
        {
            return component_serialisers.at(std::type_index(typeid(Transform)));
        }

        if (component_type_lowercase == "camera")
        {
            return component_serialisers.at(std::type_index(typeid(Camera)));
        }

        return nullptr;
    }

    void load_resources(nlohmann::json scene_data);

    std::string SCENE_DIRECTORY;
    std::string get_full_path(const std::string& scene_name) const;

    std::shared_ptr<ResourceManager> resource_manager;

    void load_entities(Scene* scene, const nlohmann::json& scene_data, std::shared_ptr<Transform> root_transform);
    std::shared_ptr<Entity> load_entity(Scene* scene, const nlohmann::json& entity_data, std::shared_ptr<Transform> parent_transform);

    std::unordered_map<std::type_index, JSONComponentSerialiser*> component_serialisers;
};

#endif //WINTER_SCENE_SERIALIZER_H
