#ifndef WINTER_FIRST_SCENE_H
#define WINTER_FIRST_SCENE_H

#include <context/winter_context.h>
#include <memory>
#include <scene/scene.h>

class FirstScene : public Scene
{
public:
    FirstScene(std::shared_ptr<WinterContext> context, SceneID scene_id);

    void on_create() override;
    void on_destroy() override;
};

#endif // WINTER_FIRST_SCENE_H
