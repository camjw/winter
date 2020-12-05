#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTexCoord;

out vec2 TexCoords;

uniform float TOTAL_TIME;
uniform float DELTA_TIME;

uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJECTION;

void main()
{
    TexCoords = inTexCoord;
    gl_Position = MODEL * vec4(inPosition, 1.0);
}
