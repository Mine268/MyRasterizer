#include <iostream>
#include "Vector.h"

int main() {

    mr::Vector<3, float> v1, v2;
    v1.set(1.f, 2.f, 3.f);
    v2.set(7.f, 6.f, 5.f);

    auto v3 = (v1 - v2).normalization();

    return 0;
}
