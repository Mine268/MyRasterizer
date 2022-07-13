//
// Created by mine268 on 2022-7-13.
//

#pragma once

#include <cmath>

namespace mr {
    template<typename T>
    extern T zeroCheckingValue;

    template<typename T>
    bool isZero(T v)  {
        return zeroCheckingValue<T> * zeroCheckingValue<T> >= v * v;
    }

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
