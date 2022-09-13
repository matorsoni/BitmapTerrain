#ifndef BITMAP_HPP
#define BITMAP_HPP

#include <string>

// Bitmap data holder that handles image I/O.
class Bitmap
{
public:
    Bitmap();
    ~Bitmap();

    // Read grayscale image file.
    bool loadFromFile(const std::string& filename, bool shouldFlip = false);

    // Getters.
    unsigned char* data() const;
    int width() const;
    int height() const;
    int channels() const;

private:
    unsigned char* data_;
    int width_;
    int height_;
    int channels_;
};

#endif // BITMAP_HPP
