#include "Texture.hpp"

#include <iostream>
#include <cassert>

#include <glad/glad.h>
#include <stb_image.h>

using namespace std;

Texture::Texture(const std::string& filename):
    id_(0), width_(0), height_(0), channels_(0), buffer_(nullptr)
{
    // Load image from disk using stb.
    // Consider using `float *data = stbi_loadf(filename, &w, &h, &c, 0);`
    {
        int w, h, c;
        stbi_set_flip_vertically_on_load(1);
        unsigned char* data = stbi_load(filename.c_str(), &w, &h, &c, 0);

        if (data == NULL) {
            cout << "Could not load image data from file " << filename << endl;
            return;
        }

        width_ = w;
        height_ = h;
        channels_ = c;
        buffer_ = data;
    }

    // Determine the correct texture format.
    GLenum format;
    if (channels_ == 1)
        format = GL_RED;
    else if (channels_ == 2)
        format = GL_RG;
    else if (channels_ == 3)
        format = GL_RGB;
    else {
        assert(channels_ == 4);
        format = GL_RGBA;
    }

    // Create texture.
    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, format, GL_UNSIGNED_BYTE, buffer_);

    // Set texture parameters. These parameters MUST BE SET, or else we get a black texture.
    // For setting parameters per texture object, use `glTextureParameter_` functions.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Generate texture mipmap.
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free image data.
    stbi_image_free(buffer_);
    buffer_ = nullptr;

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
