#include <engine.h>
#include <entity/transform.h>
#include <utils/opengl_helpers.h>

Engine::Engine()
{
    window = std::make_shared<Window>("Estuary King");
    #ifdef WINDOWS
    window->load_icon("./assets/icon.png");
    #endif

    IMGUI_CHECKVERSION();
    imgui_context = ImGui::CreateContext();
    assert(imgui_context != nullptr && "Failed to create Dear ImGui context");

    input = std::make_unique<InputProcessor>(window);

    // Build context
    context = std::make_shared<WinterContext>();

    // Init scene manager
    scene_manager = std::make_shared<SceneManager>(context);

    // Init ui
    ui_root = std::make_shared<UIRoot>(window, context, scene_manager, imgui_context);

    // Init renderer
    renderer = std::make_unique<OpenGLRenderer>(context, window, ui_root);
}

Engine::~Engine()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Engine::run()
{
    const int UPDATE_FREQUENCY = 60;
    const float CYCLE_TIME = 1000.0f / UPDATE_FREQUENCY;

    static Timer system_timer;
    static Timer frame_timer;

    float accumulated_milliseconds = 0.0f;

    while (is_running())
    {
        system_timer.tick();
        process_input();
        accumulated_milliseconds += system_timer.get_time().delta_time;

        if (accumulated_milliseconds >= CYCLE_TIME)
        {
            accumulated_milliseconds -= CYCLE_TIME;

            frame_timer.tick();

            Time time = frame_timer.get_time();
            update(time);

            late_update(time);

            draw(time);
        }
    }
}

void Engine::update(Time time)
{
    window->update(time, input.get());
    scene_manager->update(time, input.get());
    ui_root->update();
}

void Engine::late_update(Time time)
{
    scene_manager->late_update(time, input.get());
    ui_root->late_update();
}

void Engine::draw(Time time)
{
    renderer->draw_scene(time, scene_manager->get_current_scene());
}

void Engine::process_input()
{
    input->process_input();
}

bool Engine::is_running() { return !window->should_close(); }
