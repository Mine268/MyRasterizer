#pragma once

#include <vector>

struct image {
    std::size_t height, width;
    unsigned char *buffer;

    image(std::size_t h, std::size_t w);
    ~image();
    unsigned char *at(std::size_t h, std::size_t w) const;
    void save_to(const char* pth) const;
    void clear(unsigned char c = 0) const;
};
