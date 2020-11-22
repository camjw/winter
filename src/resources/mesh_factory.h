#ifndef WINTER_MESH_FACTORY_H
#define WINTER_MESH_FACTORY_H

#include <rendering/data/mesh.h>

class MeshFactory : public ResourceFactory<Mesh>
{
public:
    explicit MeshFactory()
        : ResourceFactory("assets/meshes")
    {
    }

protected:
    inline virtual std::shared_ptr<Mesh> build(const std::string& name) override
    {
        assert("Can't load meshes from files at the moment");
        return nullptr;
    }

    inline virtual std::shared_ptr<Mesh> build_from_data(
        std::vector<float3> positions,
        std::vector<float2> uvs,
        std::vector<uint32_t> indices)
    {
        return std::make_shared<Mesh>(positions, uvs, indices);
    }
};

#endif // WINTER_MESH_FACTORY_H
