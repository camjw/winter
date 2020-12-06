#ifndef WINTER_SCENE_MANAGER_H
#define WINTER_SCENE_MANAGER_H

#include "scene.h"
#include "scene_id.h"
#include <context/winter_context.h>
#include <input/input.h>
#include <memory>
#include <serialisation/scene_serialiser.h>
#include <timer.h>

class SceneManager
{
public:
    SceneManager(std::shared_ptr<WinterContext> context);

    void update(const Time& time, const Input* input);
    void late_update(const Time& time, const Input* input);

    Scene* get_current_scene();
    Scene* get_scene(SceneID scene_id);

    SceneID load_scene(const std::string& scene_name)
    {
        Scene* new_scene = create_empty_scene(scene_name);
        scene_serialiser->load_scene(scene_name, new_scene);
        return new_scene->get_scene_id();
    }

private:
    Scene* create_empty_scene(const std::string& scene_name)
    {
        Scene* output = new Scene(context, next_scene_id, scene_name);
        scenes.insert(std::pair<SceneID, Scene*>(next_scene_id++, output));
        return output;
    }

    SceneID next_scene_id = 0;
    SceneID current_scene_id = 0;

    std::unordered_map<SceneID, Scene*> scenes;
    std::shared_ptr<WinterContext> context;

    std::unique_ptr<SceneSerialiser> scene_serialiser;
};

#endif // WINTER_SCENE_LOADER_H
