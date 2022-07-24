//
// Created by mine268 on 2022-7-15.
//

#pragma once

#include <cassert>
#include <array>
#include <iostream>

#include "mr_tookit.h"
#include "ResidualMat.h"

namespace mr {

    template<std::size_t ROW, std::size_t COL, typename T>
    class Matrix {

        std::array<T, ROW * COL> mat{};

        template<std::size_t ix, typename F, typename... Ts>
        void setRec(F &&f, Ts &&... args);

        template<std::size_t ix, typename F>
        void setRec(F &&f);

    public:

        Matrix() = default;

        template<typename... Ts>
        explicit Matrix(Ts...);

        Matrix(const Matrix &) = default;

        Matrix(Matrix &&) noexcept = default;

        Matrix &operator=(const Matrix &) = default;

        Matrix &operator=(Matrix &&) noexcept = default;

        T &at(std::size_t i, std::size_t j);

        T const &at(std::size_t i, std::size_t j) const;

        template<typename... Ts>
        Matrix &set(Ts &&...);

        template<std::size_t R, std::size_t C, typename VT>
        friend Matrix<R, C, VT> operator+(const Matrix<R, C, VT> &, const Matrix<R, C, VT> &);

        template<std::size_t R, std::size_t C, typename VT>
        friend Matrix<R, C, VT> operator-(const Matrix<R, C, VT> &, const Matrix<R, C, VT> &);

        template<std::size_t R, std::size_t C, typename VT>
        friend Matrix<R, C, VT> operator*(VT &&, const Matrix<R, C, VT> &);

        template<std::size_t R, std::size_t C, typename VT>
        friend Matrix<R, C, VT> operator*(const Matrix<R, C, VT> &, VT &&);

        template<std::size_t R, std::size_t C, typename VT>
        friend Matrix<R, C, VT> operator/(const Matrix<R, C, VT> &, VT &&);

        template<std::size_t R1, std::size_t S, std::size_t C2, typename VT>
        friend Matrix<R1, C2, VT> operator*(const Matrix<R1, S, VT> &, const Matrix<S, C2, VT> &);

        template<std::size_t VecDim, std::size_t R, typename VT>
        friend Vector<R, VT> operator*(const Matrix<R, VecDim, VT> &, const Vector<VecDim, VT> &);

        Matrix operator-() const;

        Matrix<COL, ROW, T> transpose() const;

        T norm2() const;

        T determine() const;

        Matrix inverse() const;

    };

    template<std::size_t ROW, std::size_t COL, typename T>
    template<typename... Ts>
    Matrix<ROW, COL, T>::Matrix(Ts... args) {
        this->set(args...);
    }

    template<std::size_t ROW, std::size_t COL, typename T>
    T &Matrix<ROW, COL, T>::at(std::size_t i, std::size_t j) {
        assert(i < ROW && j < COL);
        return this->mat.at(i * COL + j);
    }

    template<std::size_t ROW, std::size_t COL, typename T>
    T const &Matrix<ROW, COL, T>::at(std::size_t i, std::size_t j) const {
        assert(i < ROW && j < COL);
        return this->mat.at(i * COL + j);
    }

    template<std::size_t ROW, std::size_t COL, typename T>
    template<typename... Ts>
    Matrix<ROW, COL, T> &Matrix<ROW, COL, T>::set(Ts &&... args) {
        static_assert(sizeof...(args) <= ROW * COL, "[Matrix::set] too many arguments for assignment.");
        setRec<0>(args...);
        return *this;
    }

    template<std::size_t ROW, std::size_t COL, typename T>
    template<std::size_t ix, typename F, typename... Ts>
    void Matrix<ROW, COL, T>::setRec(F &&f, Ts &&... args) {
        static_assert(std::is_constructible_v<T, F>, "[Matrix::setRec] cant construct from input to cell type.");
        this->mat.at(ix) = f;
        setRec<ix + 1>(args...);
    }

    template<std::size_t ROW, std::size_t COL, typename T>
    template<std::size_t ix, typename F>
    void Matrix<ROW, COL, T>::setRec(F &&f) {
        static_assert(std::is_constructible_v<T, F>, "[Matrix::setRec] cant construct from input to cell type.");
        this->mat.at(ix) = f;
    }

    template<std::size_t R, std::size_t C, typename VT>
    Matrix<R, C, VT> operator+(const Matrix<R, C, VT> &lhs, const Matrix<R, C, VT> &rhs) {
        Matrix<R, C, VT> ret;
        for (std::size_t i = 0; i < R; ++i) {
            for (std::size_t j = 0; j < C; ++j) {
                ret.at(i, j) = lhs.at(i, j) + rhs.at(i, j);
            }
        }
        return std::move(ret);
    }

    template<std::size_t R, std::size_t C, typename VT>
    Matrix<R, C, VT> operator-(const Matrix<R, C, VT> &lhs, const Matrix<R, C, VT> &rhs) {
        Matrix<R, C, VT> ret;
        for (std::size_t i = 0; i < R; ++i) {
            for (std::size_t j = 0; j < C; ++j) {
                ret.at(i, j) = lhs.at(i, j) - rhs.at(i, j);
            }
        }
        return std::move(ret);
    }

    template<std::size_t R, std::size_t C, typename VT>
    Matrix<R, C, VT> operator*(VT &&v, const Matrix<R, C, VT> &rhs) {
        Matrix<R, C, VT> ret;
        for (std::size_t i = 0; i < R; ++i) {
            for (std::size_t j = 0; j < C; ++j) {
                ret.at(i, j) = v * rhs.at(i, j);
            }
        }
        return std::move(ret);
    }

    template<std::size_t R, std::size_t C, typename VT>
    Matrix<R, C, VT> operator*(const Matrix<R, C, VT> &lhs, VT &&v) {
        Matrix<R, C, VT> ret;
        for (std::size_t i = 0; i < R; ++i) {
            for (std::size_t j = 0; j < C; ++j) {
                ret.at(i, j) = lhs.at(i, j) * v;
            }
        }
        return std::move(ret);
    }

    template<std::size_t R, std::size_t C, typename VT>
    Matrix<R, C, VT> operator/(const Matrix<R, C, VT> &lhs, VT &&v) {
        Matrix<R, C, VT> ret;
        for (std::size_t i = 0; i < R; ++i) {
            for (std::size_t j = 0; j < C; ++j) {
                ret.at(i, j) = lhs.at(i, j) / v;
            }
        }
        return std::move(ret);
    }

    template<std::size_t R1, std::size_t S, std::size_t C2, typename VT>
    Matrix<R1, C2, VT> operator*(const Matrix<R1, S, VT> &lhs, const Matrix<S, C2, VT> &rhs) {
        Matrix<R1, C2, VT> ret;
        for (std::size_t i = 0; i < R1; ++i) {
            for (std::size_t j = 0; j < C2; ++j) {
                ret.at(i, j) = lhs.at(i, 0) * rhs.at(0, j);
                for (std::size_t k = 1; k < S; ++k) {
                    ret.at(i, j) = ret.at(i, j) + lhs.at(i, k) * rhs.at(k, j);
                }
            }
        }
        return std::move(ret);
    }

    template<std::size_t VecDim, std::size_t R, typename VT>
    Vector<R, VT> operator*(const Matrix<R, VecDim, VT> &lhs, const Vector<VecDim, VT> &rhs) {
        Vector<R, VT> ret{};
        for (std::size_t i = 0; i < R; ++i) {
            ret.at(i) = lhs.at(i, 0) * rhs.at(0);
            for (std::size_t k = 1; k < VecDim; ++k) {
                ret.at(i) = ret.at(i) + lhs.at(i, k) * rhs.at(k);
            }
        }
        return std::move(ret);
    }

    template<std::size_t ROW, std::size_t COL, typename T>
    Matrix<ROW, COL, T> Matrix<ROW, COL, T>::operator-() const {
        Matrix<ROW, COL, T> ret;
        for (std::size_t i = 0; i < ROW; ++i) {
            for (std::size_t j = 0; j < COL; ++j) {
                ret.at(i, j) = -this->at(i, j);
            }
        }
        return std::move(ret);
    }

    template<std::size_t ROW, std::size_t COL, typename T>
    Matrix<COL, ROW, T> Matrix<ROW, COL, T>::transpose() const {
        Matrix<COL, ROW, T> ret;
        for (std::size_t i = 0; i < ROW; ++i) {
            for (std::size_t j = 0; j < COL; ++j) {
                ret.at(j, i) = this->at(i, j);
            }
        }
        return std::move(ret);
    }

    template<std::size_t ROW, std::size_t COL, typename T>
    T Matrix<ROW, COL, T>::norm2() const {
        T ret{};
        for (std::size_t i = 0; i < ROW; ++i) {
            for (std::size_t j = 0; j < COL; ++j) {
                ret = ret + this->at(i, j) * this->at(i, j);
            }
        }
        return ret;
    }

    template<std::size_t ROW, std::size_t COL, typename T>
    T Matrix<ROW, COL, T>::determine() const {
        if constexpr (ROW == 1) {
            return this->at(0, 0);
        } else if constexpr (ROW == 2) {
            return this->at(0, 0) * this->at(1, 1) - this->at(1, 0) * this->at(0, 1);
        } else {
            decltype(this->at(0, 0) * ResidualMat<ROW - 1, COL - 1, std::remove_reference_t<decltype(*this)>>{*this, 0,
                                                                                                              0}.determine()) ret = 0;
            for (std::size_t i = 0; i < ROW; i += 2) {
                ret = ret + this->at(i, 0) *
                            ResidualMat<ROW - 1, COL - 1, std::remove_reference_t<decltype(*this)>>{*this, i,
                                                                                                    0}.determine();
            }
            for (std::size_t i = 1; i < ROW; i += 2) {
                ret = ret - this->at(i, 0) *
                            ResidualMat<ROW - 1, COL - 1, std::remove_reference_t<decltype(*this)>>{*this, i,
                                                                                                    0}.determine();
            }
            return ret;
        }
    }

    template<std::size_t ROW, std::size_t COL, typename T>
    Matrix<ROW, COL, T> Matrix<ROW, COL, T>::inverse() const {
        Matrix<ROW, COL, T> ret;
        auto det = this->determine();

        if (mr::isZero(det)) {
            std::cerr << "[RT][Matrix::inverse] this matrix maybe not invertible.";
        }

        for (std::size_t i = 0; i < ROW; ++i) {
            for (std::size_t j = 0; j < COL; ++j) {
                ret.at(j, i) = ResidualMat<ROW - 1, COL - 1, std::remove_reference_t<decltype(*this)>>{*this, i,
                                                                                                       j}.determine() /
                               det;
                if ((i + j) & 1) {
                    ret.at(j, i) = -ret.at(j, i);
                }
            }
        }

        return std::move(ret);
    }

    extern const mr::Matrix<3, 3, int> identity3i;
    extern const mr::Matrix<3, 3, float> identity3f;
    extern const mr::Matrix<3, 3, double> identity3d;

} // mr
