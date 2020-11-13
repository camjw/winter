#ifndef WINTER_WINTER_CONTEXT_H
#define WINTER_WINTER_CONTEXT_H

#include <memory>
#include <resources/material_repository.h>
#include <resources/mesh_repository.h>
#include <resources/shader_repository.h>
#include <resources/texture_repository.h>

class WinterContext
{
public:
    explicit WinterContext();

    inline std::shared_ptr<MeshRepository> get_mesh_repository()
    {
        return mesh_repository;
    }

    inline std::shared_ptr<TextureRepository> get_texture_repository()
    {
        return texture_repository;
    }

    inline std::shared_ptr<MaterialRepository> get_material_repository()
    {
        return material_repository;
    }

    inline std::shared_ptr<ShaderRepository> get_shader_repository()
    {
        return shader_repository;
    }

private:
    std::shared_ptr<MeshRepository> mesh_repository;
    std::shared_ptr<TextureRepository> texture_repository;
    std::shared_ptr<MaterialRepository> material_repository;
    std::shared_ptr<ShaderRepository> shader_repository;
};

#endif //DEMO_DEMO_CONTEXT_H
