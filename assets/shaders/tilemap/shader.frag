#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

struct Material {
    sampler2D texture;
    vec3 colour;
    bool use_texture;
};

uniform Material material;

void main()
{
    FragColor = texture(material.texture, TexCoords);
}
