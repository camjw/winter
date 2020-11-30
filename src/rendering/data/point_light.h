#ifndef WINTER_POINT_LIGHT_H
#define WINTER_POINT_LIGHT_H

#include "shader.h"
#include <maths/maths.h>

struct PointLight
{
    float3 colour;

    float constant;
    float linear;
    float quadratic;

    float3 ambient;
    float3 diffuse;
    float3 specular;

    inline void bind(Shader* shader, int index, float3 position)
    {
        shader->set_float3("pointLights[" + std::to_string(index) + "].position", position);
        shader->set_float3("pointLights[" + std::to_string(index) + "].colour", colour);
        shader->set_float("pointLights[" + std::to_string(index) + "].constant", constant);
        shader->set_float("pointLights[" + std::to_string(index) + "].linear", linear);
        shader->set_float("pointLights[" + std::to_string(index) + "].quadratic", quadratic);
        shader->set_float3("pointLights[" + std::to_string(index) + "].ambient", ambient);
        shader->set_float3("pointLights[" + std::to_string(index) + "].diffuse", diffuse);
        shader->set_float3("pointLights[" + std::to_string(index) + "].specular", specular);
    }
};

#endif //WINTER_POINT_LIGHT_H
