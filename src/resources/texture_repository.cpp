#include <resources/texture_repository.h>
#include <utils/opengl_helpers.h>

TextureRepository::TextureRepository()
{
    TextureID base_texture_id = create_texture("base_texture", "assets/textures/uv_test.png");
    printf("Base texture id: %i\n", base_texture_id);
}

Texture* TextureRepository::get_texture(TextureID texture_id)
{
    assert(textures.find(texture_id) != textures.end() && "No such texture.");

    return textures[texture_id].get();
}

TextureID TextureRepository::get_texture_id(const std::string& texture_name)
{
    assert(texture_names_to_ids.find(texture_name) != texture_names_to_ids.end() && "No such texture.");

    return texture_names_to_ids[texture_name];
}

TextureID TextureRepository::create_texture(const std::string& texture_name, const std::string& filename)
{
    if (texture_names_to_ids.find(texture_name) != texture_names_to_ids.end())
    {
        return texture_names_to_ids[texture_name];
    }

    std::unique_ptr<Texture> new_texture = std::make_unique<Texture>(filename);

    texture_names_to_ids.insert(std::make_pair(texture_name, ++current_texture_id));
    textures.insert(std::make_pair(current_texture_id, std::move(new_texture)));
    glCheckError();

    return current_texture_id;
}

void TextureRepository::delete_texture(TextureID texture_id)
{
    assert(textures.find(texture_id) != textures.end() && "Removing non-existent texture.");

    std::unique_ptr<Texture> texture_to_delete = std::move(textures[texture_id]);
    texture_to_delete->release();
    texture_to_delete.release();
    textures.erase(texture_id);
}

void TextureRepository::clear()
{
    for (auto& texture : textures)
    {
        delete_texture(texture.first);
    }
}
