#ifndef BITMAP_HPP
#define BITMAP_HPP

#include <string>

// Bitmap data holder.
class Bitmap
{
public:
    Bitmap();
    ~Bitmap();

    // Read grayscale image file.
    bool loadFromFile(const std::string& filename);

    // Getters.
    unsigned char* data();
    int width();
    int height();

private:
    unsigned char* data_;
    int width_;
    int height_;
};

#endif // BITMAP_HPP
