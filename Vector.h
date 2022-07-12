//
// Created by mine268 on 2022-7-12.
//

#pragma once

#include <type_traits>
#include <array>

namespace mr {

    template<std::size_t Dim, typename VT>
    class Vector {
        static_assert(Dim != 0, "[Vector] 0 dimension error.");

        std::array<VT, Dim> vec{};

        template<std::size_t ix, typename F, typename... Vs>
        void setRec(F first, Vs... rest);

        template<std::size_t ix, typename F>
        void setRec(F first);

    public:
        Vector() = default;

        Vector(Vector const &) = default;

        Vector(Vector&&) noexcept;

        VT &at(std::size_t ix);

        VT const &at(std::size_t ix) const;

        static VT dot(Vector const&, Vector const&) ;

        template<typename... VTs>
        Vector &set(VTs...);

        Vector &operator=(Vector const &rhs); // assignment

        Vector &operator=(Vector &&rhs) noexcept;

        Vector operator+(Vector const &rhs);// plus

        Vector operator-(Vector const &rhs); // minus

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
    };

    template<std::size_t Dim, typename VT>
    VT Vector<Dim, VT>::dot(const Vector<Dim, VT> &lhs, const Vector<Dim, VT> &rhs) {
        VT ret = lhs.at(0) * rhs.at(0);
        for (std::size_t i = 1; i < Dim; ++i) {
            ret += lhs.at(i) * rhs.at(i);
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
    Vector<Dim, VT> Vector<Dim, VT>::operator-() {
        Vector<Dim, VT> ret{};
        for (std::size_t i = 0; i < Dim; ++i) {
            ret.at(i) = -this->at(i);
        }
        return ret;
    }

    template<std::size_t Dim, typename VT>
    template<typename... VTs>
    Vector<Dim, VT> &Vector<Dim, VT>::set(VTs... args) {
        static_assert(Dim >= sizeof...(VTs), "[Vector] too many arguments for assignment.");
        this->template setRec<0>(args...);
        return *this;
    }

    template<std::size_t Dim, typename VT>
    template<std::size_t ix, typename F, typename... Vs>
    void Vector<Dim, VT>::setRec(F first, Vs... rest) {
        static_assert(std::is_constructible_v<VT, F>, "[Vector] can construct vector scalar.");
        this->at(ix) = first;
        this->template setRec<ix + 1>(rest...);
    }

    template<std::size_t Dim, typename VT>
    template<std::size_t ix, typename F>
    void Vector<Dim, VT>::setRec(F first) {
        static_assert(std::is_constructible_v<VT, F>, "[Vector] can construct vector scalar.");
        this->at(ix) = first;
    }

    template<std::size_t Dim, typename VT>
    Vector<Dim, VT>::Vector(Vector &&rhs) noexcept {
        this->vec = std::move(rhs.vec);
    }

} // rm
