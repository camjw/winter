#ifndef WINTER_SCENE_HIERARCHY_VIEWER_H
#define WINTER_SCENE_HIERARCHY_VIEWER_H

#include "ui_widget.h"
#include <scene/scene_manager.h>

class SceneHierarchyViewer : public UIWidget
{
public:
    SceneHierarchyViewer(std::shared_ptr<SceneManager> scene_manager)
        : UIWidget()
        , scene_manager(scene_manager)
    {
    }

    virtual ~SceneHierarchyViewer() {}

    virtual void draw() override;

private:
    void draw_scene_node_inspector(const Entity* entity);
    std::shared_ptr<SceneManager> scene_manager;
};

#endif //DEMO_SCENE_HIERARCHY_VIEWER_H
