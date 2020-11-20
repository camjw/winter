#ifndef WINTER_TEXTURE_REPOSITORY_HPP
#define WINTER_TEXTURE_REPOSITORY_HPP

#include <glad/glad.h>
#include <stb_image.h>

#include <cstdint>
#include <string>

struct Texture
{
    explicit Texture(int width, int height);
    explicit Texture(int width, int height, GLuint internal_format, GLuint image_format);
    explicit Texture(const std::string& filename);

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    Texture(Texture&& other) noexcept
        : id_(other.id_)
    {
        other.id_ = 0;
        other.width = 0;
        other.height = 0;
        other.image_format = 0;
    }

    Texture& operator=(Texture&& other) noexcept
    {
        if (this != &other)
        {
            release();
            std::swap(id_, other.id_);
        }

        return *this;
    }

    void bind(int texture_index) const;

    inline void release()
    {
        glDeleteTextures(1, &id_);
        id_ = 0;
    }

    inline GLuint id()
    {
        return id_;
    }

private:
    GLuint id_ = 0;
    GLuint internal_format;
    GLuint image_format;
    int width;
    int height;
    void set_image_format(int num_channels);
    void load_from_data(unsigned char* image_data);
};

struct TextureProperties
{
    GLuint wrap_s;
    GLuint wrap_t;
    GLuint min_filter;
    GLuint mag_filter;

    void apply() const
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
    }
};

const TextureProperties DEFAULT_TEXTURE_PROPERTIES = TextureProperties {
    .wrap_s = GL_REPEAT,
    .wrap_t = GL_REPEAT,
    .min_filter = GL_LINEAR,
    .mag_filter = GL_LINEAR,
};

#endif //WINTER_TEXTURE_REPOSITORY_HPP
