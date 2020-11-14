#ifndef WINTER_SCENE_H
#define WINTER_SCENE_H

#include "scene_id.h"
#include <entity/camera.h>
#include <entity/entity.h>
#include <memory>
#include <utility>

class WinterContext;
class Scene
{
public:
    Scene(std::shared_ptr<WinterContext> context, SceneID scene_id)
        : context(std::move(context))
        , scene_id(scene_id)
    {
    }

    virtual void on_create() = 0;
    virtual void on_destroy() = 0;

    virtual void on_load() {};
    virtual void on_unload() {};

    inline SceneID get_scene_id() const
    {
        return scene_id;
    }

    inline Entity* get_root_node() const
    {
        return root;
    }

    Camera* get_camera() const
    {
        return nullptr;
    }

protected:
    std::shared_ptr<WinterContext> context;

    Entity* root;
    SceneID scene_id;
};

#endif // WINTER_SCENE_H
