#ifndef WINTER_RENDERING_MESH_REPOSITORY_HPP
#define WINTER_RENDERING_MESH_REPOSITORY_HPP

#include <rendering/mesh.h>

#include <unordered_map>

class MeshRepository
{
public:
    Mesh* get_mesh(MeshID mesh_id);

    // helper functions for common meshes
    Mesh* get_or_create_square();

    MeshID get_square_id();
    MeshID get_cube_id();

    void delete_mesh(MeshID mesh_id);
    void clear();

    MeshID create_mesh(
        std::vector<float3> positions,
        std::vector<float2> uvs,
        std::vector<uint32_t> indices);

private:
    std::unordered_map<std::string, MeshID> filename_to_mesh_id;
    std::unordered_map<MeshID, std::unique_ptr<Mesh>> meshes;
    MeshID current_mesh_id = 0;

    Mesh* square_mesh = nullptr;
    Mesh* cube_mesh = nullptr;

    MeshID square_mesh_id = INVALID_MESH;
    MeshID cube_mesh_id = INVALID_MESH;
};

#endif