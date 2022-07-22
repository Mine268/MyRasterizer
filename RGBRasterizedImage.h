//
// Created by mine268 on 2022-7-21.
//

#pragma once

#include <numeric>
#include <cassert>
#include <string>

#include "mr_tookit.h"

namespace mr {

    /**
     * Raster image with rgb channels
     */
    class RGBRasterizedImage {
        // pixel value type
        using pixel_valtype = struct {
            float red, green, blue;
        };

        // height & width of the image
        std::size_t width{}, height{};
        // where image is stored
        pixel_valtype *imageArr{nullptr};
        // get int
        static int discreteFloat(float) ;

    public:

        RGBRasterizedImage(std::size_t, std::size_t);

        ~RGBRasterizedImage();

        pixel_valtype &at(std::size_t, std::size_t);

        const pixel_valtype &at(std::size_t, std::size_t) const;

        void clear();

        void writeToFile(const std::string &) const;

    };

} // mr

