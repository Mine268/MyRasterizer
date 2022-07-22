//
// Created by mine268 on 2022-7-16.
//

#pragma once

#include <numeric>

#include "TriangleMesh.h"
#include "Matrix.h"

namespace mr {

    template<std::size_t TxDim = 2>
    struct MeshObjectN {

        mr::TriangleMesh<TxDim, float> mesh;

        mr::Matrix<4, 4, float> modelMat{};

        template<typename M, typename MM>
        MeshObjectN(M &&, MM &&);

    };

    template<std::size_t TxDim>
    template<typename M, typename MM>
    mr::MeshObjectN<TxDim>::MeshObjectN(M &&m, MM &&mat)
            : mesh{std::forward<M>(m)},
              modelMat{std::forward<MM>(mat)} { }

} // mr
