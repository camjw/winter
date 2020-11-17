#ifndef WINTER_OPENGL_RENDERER_HPP
#define WINTER_OPENGL_RENDERER_HPP

#include "render_queue.h"
#include <context/winter_context.h>
#include <entity/transform.h>
#include <imgui/bindings/imgui_impl_glfw.h>
#include <imgui/bindings/imgui_impl_opengl3.h>
#include <imgui/imgui.h>
#include <rendering/framebuffer.h>
#include <rendering/material.h>
#include <rendering/point_light.h>
#include <rendering/renderbuffer.h>
#include <rendering/shader.h>
#include <rendering/shader_commands/shader_commands.h>
#include <rendering/texture.h>
#include <resources/mesh_repository.h>
#include <resources/shader_repository.h>
#include <resources/texture_repository.h>
#include <scene/scene.h>
#include <ui/ui_root.h>
#include <utils/opengl_helpers.h>
#include <window.h>

class OpenGLRenderer
{
public:
    OpenGLRenderer(std::shared_ptr<WinterContext> context, std::shared_ptr<Window> window, std::shared_ptr<UIRoot> ui_root);
    void draw_scene(const Time time, const Scene* scene);

private:
    void begin_draw(const Time time, const Scene* scene);
    void set_camera(Camera* camera_entity);
    void draw_scene_graph(const Scene* scene);
    void draw_node(const Entity* entity, const Matrix4x4& parent_transform);
    void enqueue_mesh(const Entity* entity, const Matrix4x4& parent_transform);
    void process_render_commands(const Scene* scene) const;
    void resize_framebuffers();

    std::shared_ptr<Window> window;

    std::shared_ptr<MeshRepository> mesh_repository;
    std::shared_ptr<TextureRepository> texture_repository;
    std::shared_ptr<MaterialRepository> material_repository;
    std::shared_ptr<ShaderRepository> shader_repository;

    std::unique_ptr<RenderQueue> opaque_render_queue;

    std::unique_ptr<Framebuffer> framebuffer;

    std::shared_ptr<UIRoot> ui_root;

    Camera* current_camera = nullptr;
    bool is_camera_set = false;

    void process_command(const RenderCommand& command) const;
    void end_draw();
    void draw_no_camera_scene();
    void draw_clear_colour() const;
};

#endif
