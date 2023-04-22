#include <iostream>

#include "../include/mesh.hpp"
#include "../include/OBJ_loader.hpp"
#include "../include/utils.hpp"

int main() {

    objl::Loader loader;
    bool ret = loader.LoadFile("../model/box_stack.obj");
    auto mesh_object = loader_to_mesh_object(loader, 2);

    std::cout << mesh_object[5].Ns << std::endl;
    std::cout << mesh_object[5].Ns << std::endl;
    std::cout << mesh_object[5].Ns << std::endl;

    return 0;
}
