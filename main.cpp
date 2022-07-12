#include <iostream>
#include "Vertex.h"
#include "Vector.h"

#include <array>

int main() {

    mr::Vector<3, float> v1{}, v2{};
    v1.set(1.f, 2.f, 3.f);
    v2.set(4.f, 5.f, 6.f);

    mr::Vector<3, float> v3{};
    v3 = 2 * v2 + (v1 - v2);

    auto r = mr::Vector<3, float>::dot(v1, 2 * v2 + (v1 - v2));

    return 0;
}
