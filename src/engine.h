#ifndef WINTER_ENGINE_HPP
#define WINTER_ENGINE_HPP

#include <chrono>
#include <context/winter_context.h>
#include <cstdio>
#include <input/input.h>
#include <rendering/data/shader.h>
#include <rendering/data/texture.h>
#include <rendering/opengl_renderer.h>
#include <scene/scene_manager.h>
#include <stb_image.h>
#include <thread>
#include <timer.h>
#include <ui/event_repository.h>
#include <ui/ui_root.h>
#include <vector>
#include <window.h>

class Engine
{

public:
    explicit Engine();
    ~Engine();

    void run();

private:
    void process_input();

    void update(Time time);
    void late_update(Time time);
    void draw(Time time);

    bool is_running();

    std::shared_ptr<Window> window;
    std::unique_ptr<Input> input;
    std::unique_ptr<EventRepository> event_repository;

    std::shared_ptr<UIRoot> ui_root;

    std::shared_ptr<WinterContext> context;

    std::shared_ptr<SceneManager> scene_manager;
    std::unique_ptr<OpenGLRenderer> renderer;

    ImGuiContext* imgui_context = nullptr;
};
#endif
