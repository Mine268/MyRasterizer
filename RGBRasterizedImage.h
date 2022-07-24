//
// Created by mine268 on 2022-7-21.
//

#pragma once

#include <numeric>
#include <cassert>
#include <string>
#include <tuple>

#include "mr_tookit.h"
#include "ChannelImage.h"

namespace mr {

    /**
     * Raster image with rgb channels
     */
    class RGBRasterizedImage {

        using pixel = std::tuple<float, float, float>;

        enum class ChannelSelector : std::size_t { RED = 0, GREEN = 1, BLUE = 2 };

        // image storage
        mr::ChannelImage<float, float, float> image;
        // height & width of the image
        std::size_t width{}, height{};
        // where image is stored
        // get int
        static int discreteFloat(float) ;

    public:

        RGBRasterizedImage(std::size_t, std::size_t);

        pixel &at(std::size_t, std::size_t);

        const pixel &at(std::size_t, std::size_t) const;

        void clear();

        void writeToFile(const std::string &) const;

    };

} // mr

