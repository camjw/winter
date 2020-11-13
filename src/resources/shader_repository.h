#ifndef WINTER_SHADER_REPOSITORY_H
#define WINTER_SHADER_REPOSITORY_H

#include <constants/folder_constants.h>
#include <rendering/shader.h>
#include <resources/shader_repository.h>
#include <templates/action.h>
#include <utils/opengl_helpers.h>
#include <unordered_map>
#include <vector>

class ShaderRepository
{
public:
    ~ShaderRepository();
    Shader* get_shader(const ShaderID shader_id);
    Shader* get_shader(const std::string& shader_name);
    ShaderID create_shader(const std::string& shader_name, const std::string& vertex_filename, const std::string& fragment_filename);
    ShaderID create_shader(const std::string& shader_name);

    void delete_shader(ShaderID mesh_id);
    void clear();
    void for_each(std::function<void(Shader*)> action);

    std::vector<Shader*> get_all();

private:
    std::unordered_map<std::string, ShaderID> shader_name_to_shader_id;
    std::unordered_map<ShaderID, std::string> shader_id_to_shader_name;
    std::unordered_map<ShaderID, std::unique_ptr<Shader>> shaders;
    ShaderID current_shader_id = 0;
};

#endif //DEMO_SHADER_REPOSITORY_H
