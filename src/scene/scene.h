#ifndef WINTER_SCENE_H
#define WINTER_SCENE_H

#include "scene_id.h"
#include <entity/camera.h>
#include <entity/entity.h>
#include <entity/entity_manager.h>
#include <memory>
#include <utility>

class WinterContext;
class Scene
{
public:
    Scene(std::shared_ptr<WinterContext> context, SceneID scene_id, const std::string& scene_name)
        : context(std::move(context))
        , scene_id(scene_id)
        , scene_name(scene_name)
    {
        entity_manager = std::make_unique<EntityManager>(scene_name);
    }

    virtual void on_create() = 0;
    virtual void on_destroy() = 0;

    virtual void on_load() {};
    virtual void on_unload() {};

    inline SceneID get_scene_id() const
    {
        return scene_id;
    }

    inline const Entity* get_root() const
    {
        return entity_manager->get_root();
    }

    bool get_camera(Camera* camera) const
    {
        const Entity* current_entity = get_root();
        printf("Root node name %s\n", current_entity->name().c_str());
        return dfs_find_camera(current_entity, camera);
    }

private:
    bool dfs_find_camera(const Entity* current_entity, Camera* camera) const
    {
        printf("DFS at entity %s\n", current_entity->name().c_str());
        std::vector<Transform*> child_transforms = current_entity->transform->children;
        for (int i = 0; i < child_transforms.size(); i++)
        {
            const Entity* child_entity = child_transforms[i]->entity();
            printf("Child entity name %s\n", child_entity->name().c_str());
            if (child_entity->has_component<Camera>())
            {
                std::shared_ptr<Camera> entity_camera = child_entity->get_component<Camera>();
                *camera = *(entity_camera.get());
                return true;
            }

            if (dfs_find_camera(child_entity, camera))
            {
                return true;
            }
        }

        return false;
    }

protected:
    std::shared_ptr<WinterContext> context;
    std::unique_ptr<EntityManager> entity_manager;

    SceneID scene_id;

    const std::string& scene_name;
};

#endif // WINTER_SCENE_H
