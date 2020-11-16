#include "scene_hierarchy_viewer.h"
#include <entity/transform.h>

void SceneHierarchyViewer::draw()
{
    ImGui::Begin("Scene Hierarchy", &is_active, ImGuiWindowFlags_MenuBar);

    if (ImGui::TreeNode("Current Scene"))
    {
        Scene* current_scene = scene_manager->get_current_scene();
        const Entity* root_node = current_scene->get_root();
        draw_scene_node_inspector(root_node);
        ImGui::TreePop();
    }

    ImGui::End();
}

void SceneHierarchyViewer::draw_scene_node_inspector(const Entity* entity)
{
    std::vector<Transform*> children = entity->transform->children;

    for (int i = 0; i < children.size(); i++)
    {
        const Entity* child_entity = children[i]->entity();
        const std::string& name = child_entity->name();

        ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick);
        draw_scene_node_inspector(child_entity);
    }
}