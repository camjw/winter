#include <utils/opengl_helpers.h>
#include <rendering/mesh.h>

std::unique_ptr<Mesh> Mesh::primitive_mesh(int sides, bool rotate_by_half_segment)
{
    std::vector<float3> mesh_positions = {
        float3(-1.0f, -1.0f, 0.0f),
        float3(-1.0f, 1.0f, 0.0f),
        float3(1.0f, 1.0f, 0.0f),
        float3(1.0f, -1.0f, 0.0f),
    };

    std::vector<float3> mesh_normals = {
        float3(0.0f, 0.0f, 1.0f),
        float3(0.0f, 0.0f, 1.0f),
        float3(0.0f, 0.0f, 1.0f),
        float3(0.0f, 0.0f, 1.0f)
    };

    std::vector<float2> mesh_uvs = {
        float2(0.0f, 0.0f),
        float2(0.0f, 1.0f),
        float2(1.0f, 1.0f),
        float2(1.0f, 0.0f)
    };

    std::vector<uint32_t> mesh_indices = {
        0, 2, 1, 0, 3, 2
    };

    return std::make_unique<Mesh>(mesh_positions, mesh_normals, mesh_uvs, mesh_indices);
}

void Mesh::init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER,
        (positions.size() + normals.size()) * sizeof(float3) + uvs.size() * sizeof(float2),
        NULL,
        GL_STATIC_DRAW);

    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        positions.size() * sizeof(float3),
        &positions[0]);

    glBufferSubData(
        GL_ARRAY_BUFFER,
        positions.size() * sizeof(float3),
        normals.size() * sizeof(float3),
        &normals[0]);

    glBufferSubData(
        GL_ARRAY_BUFFER,
        (positions.size() + normals.size()) * sizeof(float3),
        uvs.size() * sizeof(float2),
        &uvs[0]);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float3),
        0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float3),
        (void*)(positions.size() * sizeof(float3)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float2),
        (void*)((positions.size() + normals.size()) * sizeof(float3)));

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

    glCheckError();
}

void Mesh::bind() const
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void Mesh::draw() const
{
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::bind_and_draw() const
{
    bind();
    draw();
}

void Mesh::destroy()
{
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &EBO);
}
