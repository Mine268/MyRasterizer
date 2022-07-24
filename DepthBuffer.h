//
// Created by mine268 on 2022-7-24.
//

#pragma once

#include <numeric>

#include "ChannelImage.h"

namespace mr {

    class DepthBuffer {

        std::size_t width, height;

        ChannelImage<float> depthBuffer;

    public:

        DepthBuffer(std::size_t w, std::size_t h);

        float &at(std::size_t i, std::size_t j);

        const float &at(std::size_t i, std::size_t j) const;

    };

} // mr
