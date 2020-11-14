#include <rendering/opengl_renderer.h>

OpenGLRenderer::OpenGLRenderer(std::shared_ptr<WinterContext> context,
    std::shared_ptr<Window> window, std::shared_ptr<UIRoot> ui_root)
    : window(window)
    , ui_root(ui_root)
{
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glCheckError();

    mesh_repository = context->get_mesh_repository();
    texture_repository = context->get_texture_repository();
    material_repository = context->get_material_repository();
    shader_repository = context->get_shader_repository();

    opaque_render_queue = std::make_unique<RenderQueue>();
    std::make_unique<RenderQueue>();

    // Build framebuffer
    framebuffer = std::make_unique<Framebuffer>(window->width(), window->height());
}

void OpenGLRenderer::begin_draw(const Time time, const Scene* scene)
{
    glfwPollEvents();

    shader_repository->for_each(SetShaderTime(time));

    if (window->has_dirty_size)
    {
        resize_framebuffers();
        window->has_dirty_size = false;
    }

    is_camera_set = false;

    ui_root->new_frame();
}

void OpenGLRenderer::resize_framebuffers()
{
    framebuffer.reset();
    framebuffer = std::make_unique<Framebuffer>(window->width(), window->height());
}

void OpenGLRenderer::draw_scene_graph(const Scene* scene)
{
    opaque_render_queue->clear();
    set_camera(scene->get_camera());
    Matrix4x4 transform = Matrix4x4::identity();
    draw_node(scene->get_root_node(), transform);
}

void OpenGLRenderer::draw_node(const Entity* entity, const Matrix4x4& parent_transform)
{
    Matrix4x4 node_transform = Matrix4x4::identity();

    std::shared_ptr<Transform> entity_transform = entity->transform;
    for (Transform* const& child : entity_transform->get_children())
    {
        draw_node(child->entity(), parent_transform * node_transform);
    }
}

void OpenGLRenderer::enqueue_mesh(const Entity* entity, const Matrix4x4& parent_transform)
{

}

void OpenGLRenderer::process_render_commands(const Scene* scene) const
{
    framebuffer->bind();

    float3 clear_colour = current_camera->clear_colour;
    glClearColor(clear_colour.x, clear_colour.y, clear_colour.z, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_FRAMEBUFFER_SRGB);
    glDisable(GL_BLEND);
    glViewport(0, 0, window->width(), window->height());

    for (const RenderCommand& command : opaque_render_queue->commands)
    {
        process_command(command);
    }

    framebuffer->unbind();
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_FRAMEBUFFER_SRGB);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int2 viewportDimensions = window->get_viewport_dimensions();
    glViewport(0, 0, viewportDimensions.x, viewportDimensions.y);
    Shader* deferred_shader = shader_repository->get_shader("deferred_lighting");

    deferred_shader->bind();

    framebuffer->bind_textures();
    glCheckError();

    mesh_repository->get_or_create_square()->bind_and_draw();
    glCheckError();
}

void OpenGLRenderer::end_draw()
{
    glfwSwapBuffers(window->get_glfw_window());
}

void OpenGLRenderer::set_camera(Camera* camera)
{
    current_camera = camera;
    float aspect_ratio = window->get_aspect_ratio();

    const Matrix4x4& projection_matrix = camera->get_projection_matrix();
    const Matrix4x4& view_matrix = camera->get_view_matrix(aspect_ratio);

    shader_repository->for_each(SetShaderProjection(projection_matrix));
    shader_repository->for_each(SetShaderCamera(view_matrix));

    is_camera_set = true;
}

void OpenGLRenderer::draw_scene(const Time time, const Scene* scene)
{
    begin_draw(time, scene);
    // TODO: add screen culling here
    draw_scene_graph(scene);
    process_render_commands(scene);
    ui_root->draw();
    end_draw();
}

void OpenGLRenderer::process_command(const RenderCommand& command) const
{
    Shader* shader = shader_repository->get_shader(command.shader_id);

    Material* material  = material_repository->get_material(command.material_id);
    shader->bind();
    shader->set_mat4(WINTER_CONSTANTS_MODEL, command.transform);

    shader->set_int("material.texture", 0);
    texture_repository->get_texture(command.texture_id)->bind(0);

    shader->set_bool("material.use_texture", material->use_texture);
    shader->set_float3("material.use_texture", material->colour);

    mesh_repository->get_mesh(command.mesh_id)->bind_and_draw();
}
