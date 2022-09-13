#include "Bitmap.hpp"

// Create stb_image implementation. Only define it once in this project.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Bitmap::Bitmap():
    data_(nullptr), width_(0), height_(0)
{
}

Bitmap::~Bitmap()
{
    if (data_ != nullptr) {
        stbi_image_free(data_);
        data_ = nullptr;
    }
}

bool Bitmap::loadFromFile(const std::string& filename)
{
    int w, h, c;
    unsigned char* data = stbi_load(filename.c_str(), &w, &h, &c, 1);

    if (data == nullptr || w <= 0 || h <= 0 || c != 1) {
        return false;
    }

    data_ = data;
    width_ = w;
    height_ = h;

    return true;
}

unsigned char* Bitmap::data()
{
    return data_;
}

int Bitmap::width()
{
    return width_;
}

int Bitmap::height()
{
    return height_;
}
