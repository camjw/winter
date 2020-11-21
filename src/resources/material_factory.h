#ifndef WINTER_MATERIAL_FACTORY_H
#define WINTER_MATERIAL_FACTORY_H

#include "resource_factory.h"
#include "resource_handle.h"
#include "resource_manager.h"
#include <maths/colour.h>
#include <nlohmann/json.hpp>
#include <rendering/material.h>

class MaterialFactory : public ResourceFactory<Material>
{
public:
    explicit MaterialFactory(std::shared_ptr<ResourceManager> resource_manager)
        : ResourceFactory("assets/materials")
        , resource_manager(resource_manager)
    {
    }

    inline virtual std::shared_ptr<Material> build(const std::string& name) override
    {
        nlohmann::json material_data;

        std::ifstream material_stream(get_full_path(name));
        material_stream >> material_data;

        colour colour;

        colour.r = material_data["color"]["r"];
        colour.g = material_data["color"]["g"];
        colour.b = material_data["color"]["b"];
        colour.a = material_data["color"]["a"];

        RenderMode render_mode = render_mode_from_string(material_data["render_mode"]);

        ResourceHandle shader = resource_manager->load<Shader>(material_data["shader"]);
        ResourceHandle texture = resource_manager->load<Texture>(material_data["texture"]);

        bool use_texture = texture != ResourceHandle::invalid_handle<Texture>();

        Material material = Material {
            .colour = colour,
            .texture = texture,
            .shader = shader,
            .use_texture = use_texture,
            .render_mode = render_mode,
        };

        return std::make_shared<Material>(material);
    }

private:
    std::shared_ptr<ResourceManager> resource_manager;
};

#endif // WINTER_MATERIAL_FACTORY_H
