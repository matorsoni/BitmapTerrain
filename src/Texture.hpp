#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

class Texture
{
public:
    Texture();

    // Create texture from image.
    void create(unsigned char* data, int width, int height, int channels);
    // Bind texture to a specific slot.
    void bind(int slot = 0) const;
    // Unbind texture.
    void unbind() const;

private:
    unsigned int id_;
};

#endif // TEXTURE_HPP
