#include "Texture.hpp"

#include <cassert>

#include <glad/glad.h>

Texture::Texture():
    id_(0)
{
}

void Texture::create(unsigned char* data, int width, int height, int channels)
{
    assert(data);
    assert(width > 0);
    assert(height > 0);

    // Determine the correct texture format.
    GLenum format;
    if (channels == 1)
        format = GL_RED;
    else if (channels == 2)
        format = GL_RG;
    else if (channels == 3)
        format = GL_RGB;
    else {
        assert(channels == 4);
        format = GL_RGBA;
    }

    // Create texture.
    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    // Set texture parameters. These parameters MUST BE SET, or else we get a black texture.
    // For setting parameters per texture object, use `glTextureParameter_` functions.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Generate texture mipmap.
    glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind texture.
    unbind();
}

void Texture::bind(int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
