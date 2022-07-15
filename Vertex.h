//
// Created by mine268 on 2022-7-12.
//

#pragma once

#include <array>
#include <type_traits>
#include "Vector.h"

namespace mr {

    template<std::size_t Dim = 3, std::size_t TextureDim = 2, typename VT = float>
    struct Vertex {
        Vector<Dim, VT> position;
        Vector<Dim, VT> normal;
        Vector<TextureDim, VT> texture;

        Vertex() = default;

        Vertex(Vertex const &) = default;

        Vertex(Vertex &&) noexcept = default;

        Vertex& operator=(Vertex const &) = default;

        Vertex& operator=(Vertex &&) noexcept = default;
    };

} // mr
