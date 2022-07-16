#include <iostream>

#include "MeshObject.h"
#include "ObjectLoader.h"
#include "Matrix.h"
#include "mr_tookit.h"

int main() {

    mr::Matrix<4, 4, float> model{2, 0, 0, 0,
                                  0, 2, 0, 0,
                                  0, 0, 2, 0,
                                  0, 0, 0, 1};
    mr::Matrix<4, 4, float> view{1, 0, 0, 0,
                                 0, 1, 0, 0,
                                 0, 0, 1, 0,
                                 0, 0, 0, 1};
    mr::Matrix<4, 4, float> proj{1, 0, 0, 0,
                                 0, 1, 0, 0,
                                 0, 0, 1, 0,
                                 0, 0, 0, 1};

    mr::ObjectLoader ol;
    mr::MeshObject<2, float> obj{ol.loadObject("../test/sphere.obj"), model, view, proj};

    auto r1 = obj.getModelTriangle(0);
    auto r2 = obj.getWorldTriangle(0);

    return 0;
}
