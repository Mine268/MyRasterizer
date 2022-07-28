//
// Created by mine268 on 2022-7-24.
//

#include "Scene.h"
#include "Matrix.h"
#include "DepthBuffer.h"

#include <utility>

namespace mr {

    Scene::Scene(Camera cam, std::size_t w, std::size_t h) : camera{std::move(cam)}, image{w, h}, depthBuffer{w, h} {}

    void Scene::render(const std::string &path) {
        const auto proj_mat = mr::Matrix<4, 4, float>{};
        for (auto &object : objects) {
            const auto model_mat = object.getModelMat();
            const auto view_mat = camera.getCameraMatrix();
        }
    }

    void Scene::renderLightOnObject(const mr::MeshObject<2> &obj, const Light &light) {

    }

} // mr