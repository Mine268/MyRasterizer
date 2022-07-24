#include <iostream>
#include <cmath>

#include "RGBRasterizedImage.h"
#include "MeshObject.h"
#include "ObjectLoader.h"
#include "Matrix.h"
#include "Vector.h"
#include "Camera.h"
#include "ParallelLight.h"
#include "mr_tookit.h"

int main() {

    mr::ObjectLoader loader;
    auto mesh = loader.loadObject(std::string{"../test/sphere.obj"});

    mr::MeshObject meshObject{mesh};
    meshObject.scaleX(2.0)
            .rotate(mr::Vector3f{1, 2, 1}, 1.2)
            .translate(mr::Vector3f{1, 2, 3});

    mr::Camera cam{10, 10, 0.2,
                   mr::Vector3f{0, 0, 1},
                   mr::Vector3f{-1, 0, -1},
                   mr::Vector3f{-1, 0, 1}};

    mr::ParallelLight pLight = mr::ParallelLight{
            mr::Vector3f{-1, -1, -1},
            mr::Vector3f{.5, .25, .75}
    };

    return 0;
}
