#pragma once

#include "../include/mesh.hpp"
#include "../include/OBJ_loader.hpp"


mesh_object loader_to_mesh_object(const objl::Loader&, std::size_t);
