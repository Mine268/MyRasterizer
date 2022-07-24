//
// Created by mine268 on 2022-7-24.
//

#pragma once

#include <cassert>
#include <vector>
#include <tuple>

namespace mr {

    template<typename... Ts>
    class ChannelImage {

        std::size_t width{}, height{};

        std::vector<std::tuple<Ts...>> arr;

    public:

        ChannelImage(std::size_t w, std::size_t h);

        std::size_t getWidth() const;

        std::size_t getHeight() const;

        std::tuple<Ts...> &at(std::size_t i, std::size_t j);

        const std::tuple<Ts...> &at(std::size_t i, std::size_t j) const;

    };

    template<typename... Ts>
    ChannelImage<Ts...>::ChannelImage(std::size_t w, std::size_t h) : width{w}, height{h},
                                                                      arr{std::vector<std::tuple<Ts...>>(w * h)} {
        assert(w > 0 && h > 0);
    }

    template<typename... Ts>
    std::size_t ChannelImage<Ts...>::getWidth() const {
        return width;
    }

    template<typename... Ts>
    std::size_t ChannelImage<Ts...>::getHeight() const {
        return height;
    }

    template<typename... Ts>
    std::tuple<Ts...> &ChannelImage<Ts...>::at(std::size_t i, std::size_t j) {
        assert(i < height && j < width);
        return arr.at(i * width + j);
    }

    template<typename... Ts>
    const std::tuple<Ts...> &ChannelImage<Ts...>::at(std::size_t i, std::size_t j) const {
        assert(i < height && j < width);
        return arr.at(i * width + j);
    }

} // mr
