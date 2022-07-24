//
// Created by mine268 on 2022-7-24.
//

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

} // mr