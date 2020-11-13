#ifndef DEMO_FRAMEBUFFER_H
#define DEMO_FRAMEBUFFER_H

#include "renderbuffer.h"
#include "texture.h"
#include <glad/glad.h>
#include <string>
#include <unordered_map>

class Framebuffer
{
public:
    Framebuffer(int width, int height);

    inline void bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, id_);
    }

    inline void clear()
    {

    }

    Framebuffer(const Framebuffer&) = delete;
    Framebuffer& operator=(const Framebuffer&) = delete;

    Framebuffer(Framebuffer&& other) noexcept
    : id_(other.id_)
    {
        other.id_ = 0;
    }

    Framebuffer& operator=(Framebuffer&& other) noexcept
    {
        if (this != &other)
        {
            release();
            std::swap(id_, other.id_);
        }

        return *this;
    }

    inline GLuint id() const
    {
        return id_;
    }

    inline void unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    inline void release()
    {
        glDeleteFramebuffers(1, &id_);
    }

    inline void attach(Texture* texture, int binding_index)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + binding_index, GL_TEXTURE_2D, texture->id(), 0);
    }

    inline void attach(Texture* texture, int binding_index, int mipmap_level)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + binding_index, GL_TEXTURE_2D, texture->id(), mipmap_level);
    }

    inline void attach(Renderbuffer* render_buffer)
    {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, render_buffer->id());
    }

    inline bool is_complete() const
    {
        return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    }

    void bind_textures() const;
    void bind_texture(int texture_index) const;

private:
    GLuint id_;

    std::unique_ptr<Texture> position_texture;
    std::unique_ptr<Texture> normal_texture;
    std::unique_ptr<Texture> colour_texture;

    std::unique_ptr<Renderbuffer> renderbuffer;
};

#endif //DEMO_FRAMEBUFFER_H
