//
// Created by mine268 on 2022-7-16.
//

#pragma once

#include <cassert>
#include <functional>
#include <iostream>

#include "mr_tookit.h"

namespace mr {

    template<std::size_t ROW, std::size_t COL, typename T>
    class ResidualMat {

        static_assert(ROW == COL, "[ResidualMat] 2x3 determine?");

        const T &mat;

        std::size_t Ix{}, Jx{};

    public:

        template<typename VT>
        ResidualMat(Matrix<ROW + 1, COL + 1, VT> const &, std::size_t, std::size_t);

        template<typename VT>
        ResidualMat(ResidualMat<ROW + 1, COL + 1, VT> const &, std::size_t, std::size_t);

        auto const &at(std::size_t, std::size_t) const;

        auto determine() const;

    };

    template<std::size_t ROW, std::size_t COL, typename T>
    template<typename VT>
    ResidualMat<ROW, COL, T>::ResidualMat(const Matrix<ROW + 1, COL + 1, VT> &m, std::size_t i, std::size_t j)
            : mat{m}, Ix{i}, Jx{j} {}

    template<std::size_t ROW, std::size_t COL, typename T>
    template<typename VT>
    ResidualMat<ROW, COL, T>::ResidualMat(const ResidualMat<ROW + 1, COL + 1, VT> &m, std::size_t i, std::size_t j)
            : mat{m}, Ix{i}, Jx{j} {}

    template<std::size_t ROW, std::size_t COL, typename T>
    auto const &ResidualMat<ROW, COL, T>::at(std::size_t i, std::size_t j) const {
        assert(i < ROW && j < COL);
        if (i >= Ix) ++i;
        if (j >= Jx) ++j;
        return mat.at(i, j);
    }

    template<std::size_t ROW, std::size_t COL, typename T>
    auto ResidualMat<ROW, COL, T>::determine() const {
        if constexpr (ROW == 1) {
            return this->at(0, 0);
        } else if constexpr (ROW == 2) {
            return this->at(0, 0) * this->at(1, 1) - this->at(1, 0) * this->at(0, 1);
        } else {
            decltype(this->at(0, 0) * ResidualMat<ROW - 1, COL - 1, decltype(*this)>{*this, 0, 0}.determine()) ret = 0;
            for (std::size_t i = 0; i < ROW; i += 2) {
                ret = ret + this->at(i, 0) * ResidualMat<ROW - 1, COL - 1, decltype(*this)>{*this, i, 0}.determine();
            }
            for (std::size_t i = 1; i < ROW; i += 2) {
                ret = ret - this->at(i, 0) * ResidualMat<ROW - 1, COL - 1, decltype(*this)>{*this, i, 0}.determine();
            }
            return ret;
        }
    }

} // mr
