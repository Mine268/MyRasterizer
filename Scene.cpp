//
// Created by mine268 on 2022-7-24.
//

#include "Scene.h"

#include <utility>

namespace mr {

    Scene::Scene(Camera cam, std::size_t w, std::size_t h) : camera{std::move(cam)}, image{w, h} {}

    void Scene::render(const std::string &path) {
        for (auto &object : objects) {
            for (auto &light : lights) {
                renderLightOnObject(object, light);
            }
        }
    }

    void Scene::renderLightOnObject(const mr::MeshObject<2> &obj, const Light &light) {

    }

} // mr