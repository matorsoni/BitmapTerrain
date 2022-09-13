#include "Bitmap.hpp"

// Create stb_image implementation. Only define it once in this project.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Bitmap::Bitmap():
    data_(nullptr), width_(0), height_(0), channels_(0)
{
}

Bitmap::~Bitmap()
{
    if (data_ != nullptr) {
        stbi_image_free(data_);
        data_ = nullptr;
    }
}

bool Bitmap::loadFromFile(const std::string& filename, bool shouldFlip)
{
    if (shouldFlip) {
        stbi_set_flip_vertically_on_load(1);
    }

    data_ = stbi_load(filename.c_str(), &width_, &height_, &channels_, 0);

    return data_ && width_ > 0 && height_ > 0;
}

unsigned char* Bitmap::data() const
{
    return data_;
}

int Bitmap::width() const
{
    return width_;
}

int Bitmap::height() const
{
    return height_;
}

int Bitmap::channels() const
{
    return channels_;
}
