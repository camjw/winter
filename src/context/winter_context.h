#ifndef WINTER_WINTER_CONTEXT_H
#define WINTER_WINTER_CONTEXT_H

#include <memory>
#include <resources/material_factory.h>
#include <resources/mesh_factory.h>
#include <resources/resource_manager.h>
#include <resources/shader_factory.h>
#include <resources/texture_factory.h>

class WinterContext
{
public:
    explicit WinterContext();

    inline std::shared_ptr<ResourceManager> get_resource_manager()
    {
        return resource_manager;
    }

private:
    void load_default_meshes();
    void load_default_shaders();
    std::shared_ptr<ResourceManager> resource_manager;
};

#endif //DEMO_DEMO_CONTEXT_H
