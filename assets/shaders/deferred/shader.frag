#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D render_texture;

void main()
{
    FragColor = vec4(vec3(texture(render_texture, TexCoord)), 1.0f);
}