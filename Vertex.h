//
// Created by mine268 on 2022-7-12.
//

#pragma once

#include <array>
#include <type_traits>
#include "Vector.h"

namespace mr {

    template<typename VT = float, std::size_t Dim = 3, std::size_t TextureDim = 3>
    struct Vertex {
        Vector<Dim, VT> position;
        Vector<Dim, VT> normal;
        Vector<TextureDim, VT> texture;
    };

} // mr
