#include "framebuffer.h"
#include <utils/opengl_helpers.h>

Framebuffer::Framebuffer(int width, int height)
{
    glGenFramebuffers(1, &id_);
    bind();

    colour_texture = std::make_unique<Texture>(width, height);
    renderbuffer = std::make_unique<Renderbuffer>(width, height);

    colour_texture->bind(0);
    DEFAULT_TEXTURE_PROPERTIES.apply();
    attach(colour_texture.get(), 0);

    unsigned int attachments[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, attachments);

    renderbuffer->bind();
    attach(renderbuffer.get());
    if (!is_complete())
    {
        printf("Frame buffer is not complete!\n");
    }

    unbind();
    glCheckError();
}

void Framebuffer::bind_textures() const
{
    colour_texture->bind(0);
}

void Framebuffer::bind_texture(int texture_index) const
{
    colour_texture->bind(texture_index);
}