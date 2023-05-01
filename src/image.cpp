#include <cassert>

#include "../include/stb_image_write.hpp"
#include "../include/image.hpp"

image::image(std::size_t h, std::size_t w) {
    height = h;
    width = w;
    buffer = new unsigned char [3 * height * width];
}

image::~image() {
    delete[] buffer;
}

unsigned char *image::at(std::size_t h, std::size_t w) const {
    assert(h < height && w < width);
    return buffer + 3 * (h * width + w);
}

void image::clear(unsigned char c) const {
    for (std::size_t i = 0; i < 3 * height * width; ++i)
        buffer[i] = c;
}

void image::save_to(const char *pth) const {
    image new_image {height, width};
    for (auto h_ix = 0; h_ix < height; ++h_ix) {
        for (auto w_ix = 0; w_ix < width; ++w_ix) {
            new_image.at(height - 1 - h_ix, w_ix)[0] = at(h_ix, w_ix)[0];
            new_image.at(height - 1 - h_ix, w_ix)[1] = at(h_ix, w_ix)[1];
            new_image.at(height - 1 - h_ix, w_ix)[2] = at(h_ix, w_ix)[2];
        }
    }
    stbi_write_bmp(pth, new_image.width, new_image.height, 3, new_image.buffer);
}
