#ifndef WINTER_SPOT_LIGHT_HPP
#define WINTER_SPOT_LIGHT_HPP

#include "shader.h"
#include <ecs/world.h>
#include <maths/float3.h>
#include <maths/float4.h>

struct SpotLight
{
    float3 direction;

    float inner_cone_angle;
    float outer_cone_angle;

    float3 ambient;
    float3 diffuse;
    float3 specular;

    inline void bind(Shader* shader, int index, float3 position)
    {
        shader->set_float3("spotLights[" + std::to_string(index) + "].position", position);
        shader->set_float3("spotLights[" + std::to_string(index) + "].direction", direction);
        shader->set_float("spotLights[" + std::to_string(index) + "].inner_cone_angle", inner_cone_angle);
        shader->set_float("spotLights[" + std::to_string(index) + "].outer_cone_angle", outer_cone_angle);
        shader->set_float3("spotLights[" + std::to_string(index) + "].ambient", ambient);
        shader->set_float3("spotLights[" + std::to_string(index) + "].diffuse", diffuse);
        shader->set_float3("spotLights[" + std::to_string(index) + "].specular", specular);
    }
};

REGISTER_COMPONENT(SpotLight, SpotLight)

#endif
