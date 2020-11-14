#include <resources/mesh_repository.h>

Mesh* MeshRepository::get_mesh(MeshID mesh_id)
{
    assert(meshes.find(mesh_id) != meshes.end() && "No such mesh.");

    return meshes[mesh_id].get();
}

MeshID MeshRepository::create_mesh(
    std::vector<float3> positions,
    std::vector<float2> uvs,
    std::vector<uint32_t> indices)
{
    std::unique_ptr<Mesh> new_mesh = std::make_unique<Mesh>(positions, uvs, indices);
    new_mesh->init();

    meshes.insert(std::make_pair(++current_mesh_id, std::move(new_mesh)));
    return current_mesh_id;
}

Mesh* MeshRepository::get_or_create_square()
{
    if (square_mesh != nullptr)
    {
        return square_mesh;
    }

    std::shared_ptr<Mesh> mesh = Mesh::build_primitive(PrimitiveType::SQUARE);
    mesh->init();

    meshes.insert(std::make_pair(++current_mesh_id, mesh));

    square_mesh = mesh.get();
    square_mesh_id = current_mesh_id;
    return square_mesh;
}

MeshID MeshRepository::get_square_id()
{
    if (square_mesh_id != INVALID_MESH)
    {
        return square_mesh_id;
    }

    get_or_create_square();
    return square_mesh_id;
}

void MeshRepository::delete_mesh(MeshID mesh_id)
{
    assert(meshes.find(mesh_id) != meshes.end() && "Removing non-existent mesh.");

    std::shared_ptr<Mesh> mesh_to_delete = meshes[mesh_id];
    mesh_to_delete->destroy();
    meshes.erase(mesh_id);
}

void MeshRepository::clear()
{
    for (auto& mesh : meshes)
    {
        delete_mesh(mesh.first);
    }
}
