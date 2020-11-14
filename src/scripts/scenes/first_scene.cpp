#include "first_scene.h"
#include <entity/transform.h>
#include <rendering/point_light.h>
#include <utils/opengl_helpers.h>

#include <utility>

FirstScene::FirstScene(std::shared_ptr<WinterContext> context, SceneID scene_id)
    : Scene(std::move(context), scene_id, "Winter")
{
}

void FirstScene::on_create()
{
    printf("Loading scene\n");

    Entity camera_entity = Entity("camera");
    std::shared_ptr<Camera> camera = camera_entity.add_component<Camera>();
    camera_entity.transform->set_position(float2(10, 10));
    camera->clear_colour = float3(1.0, 0.0, 0.0);
}

void FirstScene::on_destroy()
{
    printf("Exiting scene\n");
}