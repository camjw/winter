#include "first_scene.h"
#include <maths/transform.h>
#include <rendering/point_light.h>
#include <utils/opengl_helpers.h>

#include <utility>

FirstScene::FirstScene(std::shared_ptr<WinterContext> context, SceneID scene_id)
    : Scene(std::move(context), scene_id)
{
    clear_colour = float3(1.0, 1.0, 1.0);
}

void FirstScene::on_create()
{
    printf("Loading scene\n");
}

void FirstScene::on_destroy()
{
    printf("Exiting scene\n");
}