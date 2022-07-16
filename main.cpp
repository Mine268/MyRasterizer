#include <iostream>

#include "Matrix.h"
#include "Vector.h"
#include "ResidualMat.h"

int main() {

    mr::Matrix<4, 4, float> mat1{1, -3, 5, 7, 9, 11, 133, 15, 32, 4, 6, 84, 10, 412, 214, 16};
    auto mat2 = mat1.inverse();
    auto mat3 = mat2 * mat1;

    return 0;
}
