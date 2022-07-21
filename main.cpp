#include <iostream>

#include "RGBRasterizedImage.h"
#include "MeshObject.h"
#include "ObjectLoader.h"
#include "Matrix.h"
#include "mr_tookit.h"

int main() {

    mr::Matrix<3, 3, float> mat1;
    mat1.set(3, 0, -4, 0, 3, 0, 0, 0, 3);

    auto mat2 = mat1.inverse();
    auto mat3 = mat1 * mat2;

    return 0;
}
