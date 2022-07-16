//
// Created by mine268 on 2022-7-12.
//

#pragma once

#include <type_traits>
#include <array>
#include <iostream>
#include <algorithm>

#include "mr_tookit.h"

namespace mr {

    template<std::size_t Dim, typename VT>
    class Vector {

        static_assert(Dim != 0, "[Vector] 0 dimension error.");

        std::array<VT, Dim> vec{};

        template<std::size_t ix, typename F, typename... Vs>
        void setRec(F &&first, Vs &&... rest);

        template<std::size_t ix, typename F>
        void setRec(F &&first);

    public:
        Vector() = default;

        Vector(Vector const &) = default;

        Vector(Vector &&) noexcept;

        template<typename... VTs>
        explicit Vector(VTs &&...);

        VT &at(std::size_t ix);

        VT const &at(std::size_t ix) const;

        void normalize();

        Vector normalization() const;

        VT length() const;

        VT length2() const;

        static VT dot(Vector const &, Vector const &);

        template<typename = void>
        static VT cross(Vector<2, VT> const &, Vector<2, VT> const &);

        template<typename = void>
        static Vector<3, VT> cross(Vector<3, VT> const &, Vector<3, VT> const &);

        template<typename... VTs>
        Vector &set(VTs &&...);

        Vector<4, VT> pToVec4() const;

        Vector<3, VT> pToVec3() const;

        Vector<4, VT> vToVec4() const;

        Vector<3, VT> vToVec3() const;

        Vector &operator=(Vector const &rhs); // assignment

        Vector &operator=(Vector &&rhs) noexcept;

        Vector operator+(Vector const &rhs);// plus

        Vector operator-(Vector const &rhs); // minus

        Vector operator/(VT v); // div

        Vector operator-(); // negative

        template<typename VT1, std::size_t D, typename VT2>
        friend Vector operator*(VT1 v, Vector<D, VT2> const &rhs) { // *
            static_assert(std::is_constructible_v<VT2, VT1>, "[Vector] unable to build from scalar.");
            Vector<D, VT2> ret{rhs};
            for (std::size_t i = 0; i < D; ++i) {
                ret.at(i) = rhs.at(i) * v;
            }
            return ret;
        }

        template<typename VT1, std::size_t D, typename VT2>
        friend Vector operator*(Vector<D, VT2> const &lhs, VT1 v) { // *
            return v * lhs;
        }

        template<std::size_t D, typename VT2>
        friend std::ostream &operator<<(std::ostream &, Vector<D, VT2> const &);
    };

    template<std::size_t Dim, typename VT>
    VT Vector<Dim, VT>::dot(const Vector<Dim, VT> &lhs, const Vector<Dim, VT> &rhs) {
        VT ret = lhs.at(0) * rhs.at(0);
        for (std::size_t i = 1; i < Dim; ++i) {
            ret = ret + lhs.at(i) * rhs.at(i);
        }
        return ret;
    }

    template<std::size_t Dim, typename VT>
    VT &Vector<Dim, VT>::at(std::size_t ix) {
        return this->vec.at(ix);
    }

    template<std::size_t Dim, typename VT>
    VT const &Vector<Dim, VT>::at(std::size_t ix) const {
        return this->vec.at(ix);
    }

    template<std::size_t Dim, typename VT>
    Vector<Dim, VT> &Vector<Dim, VT>::operator=(const Vector &rhs) {
        if (&rhs == this) {
            return *this;
        } else {
            this->vec = rhs.vec;
            return *this;
        }
    }

    template<std::size_t Dim, typename VT>
    Vector<Dim, VT> &Vector<Dim, VT>::operator=(Vector &&rhs) noexcept {
        this->vec = std::move(rhs.vec);
        return *this;
    }

    template<std::size_t Dim, typename VT>
    Vector<Dim, VT> Vector<Dim, VT>::operator+(const Vector &rhs) {
        Vector<Dim, VT> ret{};
        for (std::size_t i = 0; i < Dim; ++i) {
            ret.at(i) = this->at(i) + rhs.at(i);
        }
        return ret;
    }

    template<std::size_t Dim, typename VT>
    Vector<Dim, VT> Vector<Dim, VT>::operator-(const Vector &rhs) {
        Vector<Dim, VT> ret{};
        for (std::size_t i = 0; i < Dim; ++i) {
            ret.at(i) = this->at(i) - rhs.at(i);
        }
        return ret;
    }

    template<std::size_t Dim, typename VT>
    Vector<Dim, VT> Vector<Dim, VT>::operator/(VT v) {
        Vector<Dim, VT> ret{};
        for (std::size_t i = 0; i < Dim; ++i) {
            ret.at(i) = this->at(i) / v;
        }
        return ret;
    }

    template<std::size_t Dim, typename VT>
    Vector<Dim, VT> Vector<Dim, VT>::operator-() {
        Vector<Dim, VT> ret{};
        for (std::size_t i = 0; i < Dim; ++i) {
            ret.at(i) = -this->at(i);
        }
        return ret;
    }

    template<std::size_t Dim, typename VT>
    template<typename... VTs>
    Vector<Dim, VT> &Vector<Dim, VT>::set(VTs &&... args) {
        static_assert(Dim >= sizeof...(VTs), "[Vector] too many arguments for assignment.");
        this->template setRec<0>(args...);
        return *this;
    }

    template<std::size_t Dim, typename VT>
    Vector<4, VT> Vector<Dim, VT>::pToVec4() const {
        static_assert(Dim == 3, "[Vector::pToVec4] vec3 please.");
        return Vector<4, VT>{this->at(0), this->at(1), this->at(2), mr::unitValue<VT>};
    }

    template<std::size_t Dim, typename VT>
    Vector<3, VT> Vector<Dim, VT>::pToVec3() const {
        static_assert(Dim == 4, "[Vector::pToVec4] vec4 please.");
        return Vector<3, VT>{this->at(0) / this->at(3),
                             this->at(1) / this->at(3),
                             this->at(2) / this->at(3)};
    }

    template<std::size_t Dim, typename VT>
    Vector<4, VT> Vector<Dim, VT>::vToVec4() const {
        static_assert(Dim == 3, "[Vector::pToVec4] vec3 please.");
        return Vector<4, VT>{this->at(0), this->at(1), this->at(2), mr::zeroValue<VT>};
    }

    template<std::size_t Dim, typename VT>
    Vector<3, VT> Vector<Dim, VT>::vToVec3() const {
        static_assert(Dim == 4, "[Vector::pToVec4] vec4 please.");
        return Vector<3, VT>{this->at(0), this->at(1), this->at(2)};
    }

    template<std::size_t Dim, typename VT>
    template<std::size_t ix, typename F, typename... Vs>
    void Vector<Dim, VT>::setRec(F &&first, Vs &&... rest) {
        static_assert(std::is_constructible_v<VT, F>, "[Vector] can construct vector scalar.");
        this->at(ix) = first;
        this->template setRec<ix + 1>(rest...);
    }

    template<std::size_t Dim, typename VT>
    template<std::size_t ix, typename F>
    void Vector<Dim, VT>::setRec(F &&first) {
        static_assert(std::is_constructible_v<VT, F>, "[Vector] can construct vector scalar.");
        this->at(ix) = first;
    }

    template<std::size_t Dim, typename VT>
    Vector<Dim, VT>::Vector(Vector &&rhs) noexcept {
        this->vec = std::move(rhs.vec);
    }

    template<std::size_t Dim, typename VT>
    template<typename>
    VT Vector<Dim, VT>::cross(const Vector<2, VT> &lhs, const Vector<2, VT> &rhs) {
        return lhs.at(0) * rhs.at(1) - lhs.at(1) * rhs.at(0);
    }

    template<std::size_t Dim, typename VT>
    template<typename>
    Vector<3, VT> Vector<Dim, VT>::cross(const Vector<3, VT> &lhs, const Vector<3, VT> &rhs) {
        Vector<3, VT> ret{};
        ret.set(
                lhs.at(1) * rhs.at(2) - lhs.at(2) * rhs.at(1),
                lhs.at(2) * rhs.at(0) - lhs.at(0) * rhs.at(2),
                lhs.at(0) * rhs.at(1) - lhs.at(1) * rhs.at(0)
        );
        return ret;
    }

    template<std::size_t D, typename VT2>
    std::ostream &operator<<(std::ostream &strm, const Vector<D, VT2> &rhs) {
        strm << "[ ";
        for (std::size_t i = 0; i < D; ++i) {
            strm << rhs.at(i) << ' ';
        }
        strm << "]";
        return strm;
    }

    template<std::size_t Dim, typename VT>
    void Vector<Dim, VT>::normalize() {
        auto a = this->at(0) * this->at(0);
        for (std::size_t i = 1; i < Dim; ++i) {
            a = a + this->at(i) * this->at(i);
        }
        if (isZero(a)) {
            return;
        } else {
            auto is_a = 1 / square(a);
            for (std::size_t i = 0; i < Dim; ++i) {
                this->at(i) = this->at(i) * is_a;
            }
        }
    }

    template<std::size_t Dim, typename VT>
    Vector<Dim, VT> Vector<Dim, VT>::normalization() const {
        auto ret = *this;
        ret.normalize();
        return ret;
    }

    template<std::size_t Dim, typename VT>
    VT Vector<Dim, VT>::length() const {
        auto a = this->at(0) * this->at(0);
        for (std::size_t i = 1; i < Dim; ++i) {
            a = a + this->at(i) * this->at(i);
        }
        return square(a);
    }

    template<std::size_t Dim, typename VT>
    template<typename... VTs>
    Vector<Dim, VT>::Vector(VTs &&... args) {
        this->set(args...);
    }

    template<std::size_t Dim, typename VT>
    VT Vector<Dim, VT>::length2() const {
        auto a = this->at(0) * this->at(0);
        for (std::size_t i = 1; i < Dim; ++i) {
            a = a + this->at(i) * this->at(i);
        }
        return a;
    }

} // rm
