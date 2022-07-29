#include <iostream>
#include <cmath>
#include <functional>

#include "mr_tookit.h"
#include "RGBRasterizedImage.h"
#include "MeshObject.h"
#include "ObjectLoader.h"
#include "Matrix.h"
#include "Vector.h"
#include "Camera.h"
#include "ParallelLight.h"
#include "Scene.h"

int main() {

    mr::ObjectLoader loader;
    std::string i_p{"../test/dout.ppm"};
    auto mesh = loader.loadObject(std::string{"../test/sphere.obj"});

    mr::MeshObject meshObject{mesh};
    meshObject.scaleX(4.0).scaleY(4.0).scaleZ(2.0);

    mr::Camera cam{300, 300, -.1, -100, 2,
                   mr::Vector3f{0, 0, 5},
                   mr::Vector3f{0, 0, -1},
                   mr::Vector3f{1, 0, 0}};

    mr::ParallelLight pLight = mr::ParallelLight{
            mr::Vector3f{-1, -1, -1},
            mr::Vector3f{.5, .25, .75},
            mr::Vector3f{100, 100, 100}
    };

    mr::Scene scene{cam, 100, 100};
    scene.objects.push_back(std::move(meshObject));
    scene.render(i_p);

    return 0;
}
