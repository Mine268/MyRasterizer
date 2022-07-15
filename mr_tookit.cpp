//
// Created by mine268 on 2022-7-13.
//

#include "mr_tookit.h"

namespace mr {
    template<> float zeroCheckingValue<float> = 1e-9;
    template<> double zeroCheckingValue<double> = 1e-9;
    template<> int zeroCheckingValue<int> = 0;
    template<> unsigned zeroCheckingValue<unsigned> = 0;
    template<> long zeroCheckingValue<long> = 0;
    template<> unsigned long zeroCheckingValue<unsigned long> = 0;
    template<> long long zeroCheckingValue<long long> = 0;
    template<> unsigned long long zeroCheckingValue<unsigned long long> = 0;
    template<typename T> T zeroCheckingValue{};

    int square(int v) {
        return static_cast<int>(std::sqrt(v));
    }
    long square(long v) {
        return static_cast<long>(std::sqrt(v));
    }
    long long square(long long v) {
        return static_cast<long long>(std::sqrt(v));
    }
    unsigned int square(unsigned int v) {
        return static_cast<unsigned int>(std::sqrt(v));
    }
    unsigned long square(unsigned long v) {
        return static_cast<unsigned long>(std::sqrt(v));
    }
    unsigned long long square(unsigned long long v) {
        return static_cast<unsigned long long>(std::sqrt(v));
    }
    float square(float v) {
        return std::sqrt(v);
    }
    double square(double v) {
        return std::sqrt(v);
    }
}