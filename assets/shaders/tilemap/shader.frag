#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

struct Material {
    sampler2D texture;
    vec4 colour;
    bool use_texture;
};

uniform Material material;

struct TileData {
    mat3 model;
    int tileType;
};

uniform TileData tileData;

void main()
{
    FragColor = texture(material.texture, TexCoords);
//    float tileColour = 0.001f * tileData.tileType;
//    FragColor = vec4(tileColour, tileColour, tileColour, 1.0f);
}
