#ifndef DEMO_SCENE_H
#define DEMO_SCENE_H

#include "scene_graph.h"
#include "scene_id.h"
#include <ecs/components/camera_component.h>
#include <memory>
#include <utility>

class DemoContext;
class Scene
{
public:
    Scene(std::shared_ptr<DemoContext> context, const std::shared_ptr<World>& world, SceneID scene_id)
        : context(std::move(context))
        , world(world)
        , scene_id(scene_id)
    {
        graph = std::make_unique<SceneGraph>(world, *this, scene_id);
    }

    virtual void on_create() = 0;
    virtual void on_destroy() = 0;

    virtual void on_load() {};
    virtual void on_unload() {};

    inline Entity get_camera() const
    {
        return camera;
    };

    inline Entity get_skybox() const
    {
        return skybox;
    };

    inline void set_camera(Entity camera)
    {
        this->camera = camera;
    };

    inline SceneID get_scene_id() const
    {
        return scene_id;
    }

    inline SceneNode* get_root_node() const
    {
        return graph->root().get();
    }

    inline float3 get_clear_colour() const
    {
        return clear_colour;
    }

    std::unique_ptr<SceneGraph> graph;

protected:
    std::shared_ptr<DemoContext> context;
    std::shared_ptr<World> world;

    Entity camera = INVALID_ENTITY;
    Entity skybox = INVALID_ENTITY;
    float3 clear_colour;
    SceneID scene_id;
};

#endif // DEMO_SCENE_H
