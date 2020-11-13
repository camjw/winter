#ifndef WINTER_SCENE_MANAGER_H
#define WINTER_SCENE_MANAGER_H

#include "scene.h"
#include "scene_id.h"
#include <context/winter_context.h>
#include <input/input_processor.h>
#include <memory>
#include <timer.h>

class SceneManager
{
public:
    SceneManager(std::shared_ptr<WinterContext> context);

    void update(Time time, InputState* input);
    void late_update(Time time, InputState* input);

    Scene* get_current_scene();
    Scene* get_scene(SceneID scene_id);

private:
    SceneID next_scene_id = 0;
    SceneID current_scene_id = 0;

    std::unordered_map<SceneID, Scene*> scenes;

    std::shared_ptr<WinterContext> context;
};

#endif // WINTER_SCENE_LOADER_H
