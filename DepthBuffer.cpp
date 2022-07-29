//
// Created by mine268 on 2022-7-24.
//

#include <iostream>
#include <fstream>

#include "DepthBuffer.h"

namespace mr {

    DepthBuffer::DepthBuffer(std::size_t w, std::size_t h) : width{w}, height{h}, depthBuffer{w, h} {
        assert(w > 0 && h > 0);
        for (std::size_t i = 0; i < h; ++i) {
            for (std::size_t j = 0; j < w; ++j) {
                depthBuffer.at(i, j) = -std::numeric_limits<float>::max();
            }
        }
    }

    float &DepthBuffer::at(std::size_t i, std::size_t j) {
        return std::get<0>(depthBuffer.at(i, j));
    }

    const float &DepthBuffer::at(std::size_t i, std::size_t j) const {
        return std::get<0>(depthBuffer.at(i, j));
    }

    void DepthBuffer::output(const std::string &path) const {
        std::fstream fstrm;
        fstrm.open(path, std::ios::out);

        if (fstrm.bad()) {
            std::cerr << "[RGBRasterizedImage::writeToFile] unable to open the file.\n";
        } else {
            fstrm << "P3\n";
            fstrm << width << ' ' << height << '\n';
            fstrm << "255\n";
            for (std::size_t i = 0; i < height; ++i) {
                for (std::size_t j = 0; j < width; ++j) {
                    fstrm << discreteFloat(at(i, j)) << ' '
                          << discreteFloat(at(i, j)) << ' '
                          << discreteFloat(at(i, j));
                    if (j < width - 1) {
                        fstrm << '\t';
                    }
                }
                fstrm << '\n';
            }
        }

        fstrm.close();
    }

    int DepthBuffer::discreteFloat(float v) {
        if (v > 0) return 0;
        if (v < -255) return 255;
        return 20 * -v;
    }

} // mr