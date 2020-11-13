#ifndef WINTER_SET_SHADER_DIRECTIONAL_LIGHT_H
#define WINTER_SET_SHADER_DIRECTIONAL_LIGHT_H

struct SetShaderDirectionalLights
{
    SetShaderDirectionalLights(std::vector<DirectionalLight> directional_lights)
        : directional_lights(directional_lights)
    {
    }

    void operator()(Shader* shader)
    {
        shader->bind();
        shader->set_int(DEMO_NUM_ACTIVE_DIRECTIONAL_LIGHTS, directional_lights.size());

        for (int i = 0; i < directional_lights.size(); i++)
        {
            DirectionalLight directional_light = directional_lights[i];
            directional_light.bind(shader, i);
        }
    }

private:
    std::vector<DirectionalLight> directional_lights;
};

#endif // WINTER_SET_SHADER_DIRECTIONAL_LIGHT_H
