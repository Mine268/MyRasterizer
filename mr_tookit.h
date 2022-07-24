//
// Created by mine268 on 2022-7-13.
//

#pragma once

#include <cmath>

namespace mr {

    template<typename E>
    constexpr auto toUType(E enumerator) noexcept {
        return static_cast<std::underlying_type_t<E>>(enumerator);
    }

    template<std::size_t Dim, typename VT>
    class Vector;

    template<std::size_t ROW, std::size_t COL, typename T>
    class Matrix;

    template<std::size_t ROW, std::size_t COL, typename T>
    class ResidualMat;

    template<typename T>
    extern T zeroValue;

    template<typename T>
    extern T zeroCheckingValue;

    template<typename T>
    extern T unitValue;

    template<typename T>
    bool isZero(T v)  {
        return zeroCheckingValue<T> * zeroCheckingValue<T> >= v * v;
    }

    /**
     * square function by iteration
     * @tparam T type of the input value
     * @param v the value to be squared(assume to be none-negative)
     * @return the squared value
     */
    template<typename T>
    T square(T v) {
        auto x0 = v;
        auto x1 = 0;
        while (!isZero(x0 - x1)) {
            x1 = x0;
            x0 = .5 * (x0 + v / x0);
        }
        return x0;
    }

    int square(int);
    long square(long);
    long long square(long long);
    unsigned square(unsigned);
    unsigned long square(unsigned long);
    unsigned long long square(unsigned long long);
    float square(float);
    double square(double);
}
