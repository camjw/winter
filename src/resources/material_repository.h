#ifndef WINTER_MATERIAL_REPOSITORY_H
#define WINTER_MATERIAL_REPOSITORY_H

#include <rendering/material.h>
#include <unordered_map>

class MaterialRepository
{
public:
    Material* get_material(MaterialID material_id);
    Material* get_material(const std::string& material_name);
    MaterialID get_material_id(const std::string& material_name);
    MaterialID insert_material(const Material material, const std::string& material_name);

    void delete_material(MaterialID material_id);
    void clear();

private:
    std::unordered_map<std::string, MaterialID> material_names_to_ids;
    std::unordered_map<MaterialID, std::unique_ptr<Material>> materials;
    MaterialID current_material_id = 0;
};

#endif //DEMO_MATERIAL_REPOSITORY_H
