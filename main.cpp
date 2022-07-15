#include <iostream>

#include "ObjectLoader.h"

int main() {

    mr::ObjectLoader ol{};
    auto mesh = ol.loadObject("../test/sphere.obj");

    return 0;
}
