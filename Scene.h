//
// Created by mine268 on 2022-7-24.
//

#pragma once

#include <vector>
#include <string>

#include "MeshObject.h"
#include "Camera.h"
#include "Light.h"
#include "RGBRasterizedImage.h"
#include "DepthBuffer.h"

#include <array>
#include <tuple>

namespace mr {

    // only 2-dim uv is supported here.

    struct Scene {

        mr::Camera camera;

        std::vector<mr::MeshObject<2>> objects;

        std::vector<mr::Light> lights;

        mr::RGBRasterizedImage image;

        mr::DepthBuffer depthBuffer;

        explicit Scene(mr::Camera, std::size_t, std::size_t);

        ~Scene() = default;

        void render(const std::string &);

    private:

        static bool withInTriangle(const std::array<mr::Vector<4, float>, 3> &, float, float);

        static std::tuple<float, float, float, float>
        invBarycentric(const std::array<mr::Vector<4, float>, 3> &, const std::array<mr::Vector<4, float>, 3> &,
                       float, float);

    };

} // mr
