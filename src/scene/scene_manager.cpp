#include <scene/scene_manager.h>

SceneManager::SceneManager(std::shared_ptr<WinterContext> context)
    : context(context)
{
    scene_serialiser = std::make_unique<SceneSerialiser>("scenes", context->get_resource_manager());
    SceneID first_scene = load_scene("first_scene");
    current_scene_id = first_scene;
}

void SceneManager::update(Time time, InputState* input) { }

void SceneManager::late_update(Time time, InputState* input) { }

Scene* SceneManager::get_current_scene()
{
    return scenes[current_scene_id];
}

Scene* SceneManager::get_scene(SceneID scene_id)
{
    assert(scenes.find(scene_id) != scenes.end() && "No scene with that ID");

    return scenes[scene_id];
}