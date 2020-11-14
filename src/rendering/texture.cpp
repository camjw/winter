#include <rendering/texture.h>
#include <utils/opengl_helpers.h>

Texture::Texture(int width, int height)
    : internal_format(GL_RGBA)
    , image_format(GL_RGBA)
    , width(width)
    , height(height)
{
    // Passing nullptr as the data makes an empty texture which can be used in a framebuffer
    load_from_data(nullptr);
}

Texture::Texture(int width, int height, GLuint internal_format, GLuint image_format)
    : internal_format(internal_format)
    , image_format(image_format)
    , width(width)
    , height(height)
{
    // Passing nullptr as the data makes an empty texture which can be used in a framebuffer
    load_from_data(nullptr);
    glCheckError();
}

Texture::Texture(const std::string& filename)
{
    int num_channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image_data = stbi_load(filename.c_str(), &width, &height, &num_channels, 0);

    if (image_data == nullptr)
    {
        printf("Failed to load texture\n");
        return;
    }

    set_image_format(num_channels);
    load_from_data(image_data);
}

void Texture::set_image_format(int num_channels)
{
    switch (num_channels)
    {
    case 1:
        image_format = GL_RED;
        internal_format = GL_RED;
        break;
    case 2:
        image_format = GL_RG;
        internal_format = GL_RG;
        break;
    case 3:
        image_format = GL_RGB;
        internal_format = GL_RGB;
        break;
    default:
        image_format = GL_RGBA;
        internal_format = GL_RGBA;
        break;
    }
}

void Texture::load_from_data(unsigned char* image_data)
{
    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);

    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, image_format, GL_UNSIGNED_BYTE, image_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    if (image_data)
    {
        stbi_image_free(image_data);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind(int texture_index) const
{
    glActiveTexture(GL_TEXTURE0 + texture_index);
    glBindTexture(GL_TEXTURE_2D, id_);
}
