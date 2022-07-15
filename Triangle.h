//
// Created by mine268 on 2022-7-12.
//

#pragma once

#include "Vertex.h"

namespace mr {

    template<std::size_t TxDim = 2, typename VT = float>
    class Triangle {
    public:
        Vertex<3, TxDim, VT> vertex[3];

        Triangle() = default;

        Triangle(const Triangle &) = default;

        Triangle(Triangle &&) noexcept = default;

        Triangle(Vertex<3, TxDim, VT> const&,
                 Vertex<3, TxDim, VT> const&,
                 Vertex<3, TxDim, VT> const&);

        Vector<3, VT> normal();

        VT size();

        Triangle &operator=(Triangle const &) = default;

        Triangle &operator=(Triangle &&) noexcept = default;
    };

    template<std::size_t TxDim, typename VT>
    Vector<3, VT> Triangle<TxDim, VT>::normal() {
        auto ret = Vector<3, VT>::cross(this->vertex[1].position - this->vertex[0].position,
                                        this->vertex[2].position - this->vertex[1].position);
        ret.normalize();
        return ret;
    }

    template<std::size_t TxDim, typename VT>
    VT Triangle<TxDim, VT>::size() {
        return Vector<3, VT>::cross(this->vertex[1].position - this->vertex[0].position,
                                    this->vertex[2].position - this->vertex[1].position).length() / 2;
    }

    template<std::size_t TxDim, typename VT>
    Triangle<TxDim, VT>::Triangle(const Vertex<3, TxDim, VT> &a, const Vertex<3, TxDim, VT> &b,
                                  const Vertex<3, TxDim, VT> &c) {
        vertex[0] = a;
        vertex[1] = b;
        vertex[2] = c;
    }

} // rt
