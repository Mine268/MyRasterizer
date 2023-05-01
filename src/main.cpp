#include <iostream>

#include "../include/world_object.hpp"
#include "../include/OBJ_loader.hpp"
#include "../include/utils.hpp"
#include "../include/scene.hpp"
#include "../include/camera.hpp"

int main() {

    float tmp = 1e-1f;

    objl::Loader loader;
    [[maybe_unused]] bool ret = loader.LoadFile("../model/bunny.obj");
    world_object wo {
        loader_to_mesh_object(loader, 0)
    };
    wo.translation = Eigen::Vector3f(0, -5e-2, -tmp);

    camera cam {
        Eigen::Vector3f (tmp, tmp, 0),
        Eigen::Vector3f (-tmp, -tmp, -tmp),
        Eigen::Vector3f (-tmp, tmp, -tmp),
        -1, -10,
        0.01, 500, 400
    };

    scene sc;
    sc.objects.push_back(wo);
    sc.cameras.push_back(cam);

    sc.render(0);

    return 0;
}
