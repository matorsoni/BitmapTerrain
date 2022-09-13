#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

class Texture
{
public:
    Texture(const std::string& filename);
    ~Texture() = default;

    // Bind texture to a specific slot.
    void bind(int slot = 0) const;
    // Unbind texture.
    void unbind() const;

private:
    unsigned int id_;
    int width_;
    int height_;
    int channels_;
    unsigned char* buffer_;
};

#endif // TEXTURE_HPP
