#ifndef WINTER_RENDERING_MESH_HPP
#define WINTER_RENDERING_MESH_HPP

#include <utils/opengl_include.h>

#include <maths/maths.h>
#include <string>
#include <utility>
#include <vector>

enum PrimitiveType
{
    TRIANGLE,
    SQUARE,
    HEXAGON,
    CIRCLE,
};

class Mesh
{
public:
    explicit Mesh() {};

    static Mesh build_primitive(PrimitiveType primitive_type)
    {
        switch (primitive_type)
        {
        case TRIANGLE:
            return primitive_mesh(3, false);
        case SQUARE:
            return primitive_mesh(4, true);
        case HEXAGON:
            return primitive_mesh(6, true);
        case CIRCLE:
            return primitive_mesh(32, false);
        }
    }

    Mesh(
        std::vector<float3> positions,
        std::vector<float2> uvs,
        std::vector<uint32_t> indices)
        : positions(std::move(positions))
        , uvs(std::move(uvs))
        , indices(std::move(indices)) {};

    std::vector<float3> positions;
    std::vector<float2> uvs;

    std::vector<uint32_t> indices;

    void init();
    void bind() const;
    void draw() const;
    void bind_and_draw() const;
    void destroy();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    Mesh(Mesh&& other) noexcept
        : positions(other.positions)
        , uvs(other.uvs)
        , indices(other.indices)
        , VAO(other.VAO)
        , EBO(other.EBO)
        , VBO(other.VBO)
    {
        other.VAO = 0;
        other.VBO = 0;
        other.EBO = 0;
    }

    Mesh& operator=(Mesh&& other) noexcept
    {
        if (this != &other)
        {
            destroy();
            std::swap(VAO, other.VAO);
            std::swap(VBO, other.VBO);
            std::swap(EBO, other.EBO);
        }

        return *this;
    }

    unsigned int VAO = 0;
    unsigned int EBO = 0;
    unsigned int VBO = 0;

private:
    static Mesh primitive_mesh(int sides, bool rotate_by_half_segment);
};

#endif
