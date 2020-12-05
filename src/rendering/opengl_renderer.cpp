#include <constants/shader_constants.h>
#include <rendering/data/tilemap_layer.h>
#include <rendering/data/tileset.h>
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

    resource_manager = context->get_resource_manager();

    opaque_render_queue = std::make_unique<RenderQueue>();
    std::make_unique<RenderQueue>();

    // Build framebuffer
    framebuffer = std::make_unique<Framebuffer>(window->width(), window->height());
}

void OpenGLRenderer::begin_draw(const Time time, const Scene* scene)
{
    glfwPollEvents();

    resource_manager->for_each<Shader>([time](Shader* shader) {
        shader->bind();
        shader->set_float(WINTER_CONSTANTS_TOTAL_TIME, time.total_time);
        shader->set_float(WINTER_CONSTANTS_DELTA_TIME, time.delta_time);
    });

    if (window->has_dirty_size)
    {
        resize_framebuffers();
        window->has_dirty_size = false;
    }

    Camera* camera = nullptr;
    if (scene->get_camera(&camera))
    {
        is_camera_set = true;
        set_camera(camera);
    }
    else
    {
        printf("No camera set!\n");
        is_camera_set = false;
    }

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
    float4x4 transform = float4x4::identity();
    draw_node(scene->get_root(), transform);
}

void OpenGLRenderer::draw_node(const Entity* entity, const float4x4& parent_transform)
{
    float4x4 node_transform = parent_transform * entity->transform->get_model_matrix();

    if (entity->has_component<TilemapRenderer>())
    {
        enqueue_tilemap(entity, parent_transform);
    }

    for (Transform* const& child : entity->transform->get_children())
    {
        draw_node(child->entity(), parent_transform * node_transform);
    }
}

void OpenGLRenderer::enqueue_tilemap(const Entity* entity, const float4x4& parent_transform)
{
    TilemapRenderer* tilemap_renderer = entity->get_component<TilemapRenderer>().get();
    Tilemap* tilemap = resource_manager->get<Tilemap>(tilemap_renderer->tilemap);
    Tileset tileset = *(resource_manager->get<Tileset>(tilemap->tileset));

    ResourceHandle square_mesh_handle = resource_manager->load<Mesh>("square");
    ResourceHandle material_handle = tilemap->material;

    TransformData entity_transform_data = entity->transform->get_transform_data(parent_transform);

    for (int i = 0; i < tilemap->layers.size(); i++)
    {
        TilemapLayer layer = tilemap->layers[i];
        assert(material_handle.is_of_type<Material>() && "Tilemap layer should have handle to material");

        for (int j = 0; j < layer.width; j++)
        {
            for (int k = 0; k < layer.height; k++)
            {
                int tile_type = layer.data[j][k];

                TransformData tile_transform_data = TransformData::translate(entity_transform_data, float2(j, k));
                opaque_render_queue->push_back(RenderCommand {
                    .mesh = square_mesh_handle,
                    .material = material_handle,
                    .transform = tile_transform_data.get_model_matrix(),
                    .tile_transform = calculate_tile_transform(tile_type, tileset),
                    .tile_type = tile_type
                });
            }
        }
    }
}

void OpenGLRenderer::process_render_commands(const Scene* scene) const
{
//    framebuffer->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_clear_colour();
    glCheckError();

//    glEnable(GL_DEPTH_TEST);
//    glDisable(GL_FRAMEBUFFER_SRGB);
//    glViewport(0, 0, window->width(), window->height());
    glCheckError();

    for (const RenderCommand& command : opaque_render_queue->commands)
    {
        process_command(command);
    }
    glCheckError();

//    framebuffer->unbind();
//
//    glDisable(GL_DEPTH_TEST);
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);
//    glEnable(GL_FRAMEBUFFER_SRGB);
//    glCheckError();
//
//    int2 viewportDimensions = window->get_viewport_dimensions();
//    glViewport(0, 0, viewportDimensions.x, viewportDimensions.y);
//    Shader* deferred_shader = resource_manager->get<Shader>("deferred");
//    glCheckError();
//
//    deferred_shader->bind();
//
//    framebuffer->bind_textures();
//    glCheckError();
//
//    resource_manager->get<Mesh>("square")->bind_and_draw();
//    glCheckError();
}

void OpenGLRenderer::end_draw()
{
    glfwSwapBuffers(window->get_glfw_window());
}

void OpenGLRenderer::set_camera(Camera* camera)
{
    current_camera = camera;
    float aspect_ratio = window->get_aspect_ratio();

    const float4x4& projection_matrix = camera->get_projection_matrix(aspect_ratio);
    const float4x4& view_matrix = camera->get_view_matrix();

    resource_manager->for_each<Shader>([projection_matrix, view_matrix](Shader* shader) {
        shader->bind();
        shader->set_mat4(WINTER_CONSTANTS_PROJECTION, projection_matrix);
        shader->set_mat4(WINTER_CONSTANTS_VIEW, view_matrix);
    });

    is_camera_set = true;
}

void OpenGLRenderer::draw_scene(const Time time, const Scene* scene)
{
    begin_draw(time, scene);
    if (is_camera_set)
    {
        draw_scene_graph(scene);
        process_render_commands(scene);
    }
    else
    {
        draw_no_camera_scene();
    }

    ui_root->draw();
    end_draw();
}

void OpenGLRenderer::process_command(const RenderCommand& command) const
{
    Material* material = resource_manager->get<Material>(command.material);
    Shader* shader = resource_manager->get<Shader>(material->shader);
    shader->bind();
    shader->set_mat4(WINTER_CONSTANTS_MODEL, command.transform);
    shader->set_mat3("tileData.model", command.tile_transform);
    shader->set_int("tileData.tileType", command.tile_type);
    shader->set_int("material.texture", 0);

    resource_manager->get<Texture>(material->texture)->bind(0);

    shader->set_bool("material.use_texture", material->use_texture);
    shader->set_float4("material.colour", material->colour);

    Mesh* mesh = resource_manager->get<Mesh>(command.mesh);
    mesh->bind_and_draw();
    glCheckError();
}

void OpenGLRenderer::draw_no_camera_scene()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::draw_clear_colour() const
{
    const float4 clear_colour = current_camera->clear_colour;
    glClearColor(clear_colour.x, clear_colour.y, clear_colour.z, 1.0f);
}
