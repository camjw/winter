#include <scene/scene_manager.h>
#include <scripts/scenes/first_scene.h>

SceneManager::SceneManager(std::shared_ptr<WinterContext> context)
    : context(context)
{
    Scene* first_scene = new FirstScene(context, next_scene_id);
    first_scene->on_create();

    scenes.insert(std::pair<SceneID, Scene*>(next_scene_id++, first_scene));
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