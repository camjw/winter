#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 position;

struct Material {
    sampler2D texture;
    vec4 colour;
    bool use_texture;
};

uniform Material material;

void main()
{
//    FragColor = texture(material.texture, TexCoords);
    FragColor = vec4(position.y, 0, 0, 1);
}
