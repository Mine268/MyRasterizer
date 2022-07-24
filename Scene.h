//
// Created by mine268 on 2022-7-24.
//

#pragma once

#include <vector>

#include "MeshObject.h"
#include "Camera.h"

namespace mr {

    // only 2-dim uv is supported here.

    class Scene {

        std::vector<mr::MeshObject<2>> objects;

        mr::Camera camera;

    };

} // mr
