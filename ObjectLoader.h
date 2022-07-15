//
// Created by mine268 on 2022-7-12.
//

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>

#include "TriangleMesh.h"
#include "Vector.h"

namespace mr {

    class ObjectLoader {

        static constexpr float UV_DEFAULT = 0.f;

        std::vector<mr::Vector<3, float>> positions, normals;
        std::vector<mr::Vector<2, float>> uvs;

        std::string modelName = "object";
        std::string currGroupName = "default";

        static std::tuple<float, float, float> getThreeFloats(std::string const &);

        static std::tuple<float, float> getTwoFloats(std::string const &);

        void updateTriangles(TriangleMesh<2, float> &, std::string const &);

        Vertex<3, 2, float> createVertexFromStr(const std::string &);

    public:
        TriangleMesh<2, float> loadObject(std::string const& path);
    }; // ObjectLoader

} // mr
