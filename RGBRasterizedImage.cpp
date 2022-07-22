//
// Created by mine268 on 2022-7-21.
//

#include <fstream>
#include <iostream>

#include "RGBRasterizedImage.h"

namespace mr {

    RGBRasterizedImage::RGBRasterizedImage(std::size_t w, std::size_t h) :
            width{w}, height{h}, imageArr{new pixel_valtype[w * h]} {
        assert(w > 0 && h > 0);
        clear();
    }

    RGBRasterizedImage::~RGBRasterizedImage() {
        delete[] imageArr;
    }

    RGBRasterizedImage::pixel_valtype &RGBRasterizedImage::at(std::size_t i, std::size_t j) {
        assert(i < height && j < width);
        return imageArr[i * width + j];
    }

    const RGBRasterizedImage::pixel_valtype &RGBRasterizedImage::at(std::size_t i, std::size_t j) const {
        assert(i < height && j < width);
        return imageArr[i * width + j];
    }

    void RGBRasterizedImage::clear() {
        for (std::size_t i = 0; i < width * height; ++i) {
            imageArr[i].red = imageArr[i].green = imageArr[i].blue = 0;
        }
    }

    void RGBRasterizedImage::writeToFile(const std::string &path) const {
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
                    fstrm << discreteFloat(at(i, j).red) << ' '
                          << discreteFloat(at(i, j).green) << ' '
                          << discreteFloat(at(i, j).blue);
                    if (j < width - 1) {
                        fstrm << '\t';
                    }
                }
                fstrm << '\n';
            }
        }

        fstrm.close();
    }

    int RGBRasterizedImage::discreteFloat(float f) {
        if (f < 0) f = 0;
        if (f > 1) f = 1;
        return static_cast<int>(f * 255);
    }

} // mr