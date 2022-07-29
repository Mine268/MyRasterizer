//
// Created by mine268 on 2022-7-24.
//

#include "Scene.h"
#include "Matrix.h"
#include "Vector.h"
#include "DepthBuffer.h"

#include <array>
#include <utility>
#include <iostream>
#include <numeric>

namespace mr {

    Scene::Scene(Camera cam, std::size_t w, std::size_t h) : camera{std::move(cam)}, image{w, h}, depthBuffer{w, h} {}

    void Scene::render(const std::string &path) {
        static auto clampBtw = [](float v) -> float { return std::clamp<float>(v, -1, 1); };
        const auto cam_mat = camera.getCameraMatrix();
        const auto proj_mat = camera.getProjMat();
        const auto orth_mat = camera.getOrthMat();
        const auto view_mat = camera.getViewPortMat();
        float delta_x = 2.f / static_cast<float>(camera.width),
                delta_y = 2.f / static_cast<float>(camera.height);

        for (auto &object: objects) {
            const auto model_mat = object.getModelMat();
            auto &mesh = object.getMesh();
            for (auto &triangle: mesh.getTriangles()) {
                std::array<mr::Vector<4, float>, 3> tri_cam_pos{triangle.vertex[0].position.pToVec4(),
                                                                triangle.vertex[1].position.pToVec4(),
                                                                triangle.vertex[2].position.pToVec4()};
                std::array<mr::Vector<4, float>, 3> tri_con_pos{triangle.vertex[0].position.pToVec4(),
                                                                triangle.vertex[1].position.pToVec4(),
                                                                triangle.vertex[2].position.pToVec4()};
                std::transform(tri_cam_pos.begin(),
                               tri_cam_pos.end(),
                               tri_cam_pos.begin(),
                               [&](const mr::Vector<4, float> &pos) -> mr::Vector<4, float> {
                                   auto tmp = (cam_mat * (model_mat * pos));
                                   tmp = tmp / tmp.at(3);
                                   return tmp;
                               });
                std::transform(tri_cam_pos.begin(),
                               tri_cam_pos.end(),
                               tri_con_pos.begin(),
                               [&](const mr::Vector<4, float> &pos) -> mr::Vector<4, float> {
                                   auto tmp = (orth_mat * (proj_mat * pos));
                                   tmp = tmp / tmp.at(3);
                                   return tmp;
                               });
                float minX = clampBtw(std::min(
                        std::min(tri_con_pos.at(0).at(0), tri_con_pos.at(1).at(0)),
                        tri_con_pos.at(2).at(0)));
                float maxX = clampBtw(std::max(
                        std::max(tri_con_pos.at(0).at(0), tri_con_pos.at(1).at(0)),
                        tri_con_pos.at(2).at(0)));
                float minY = clampBtw(std::min(
                        std::min(tri_con_pos.at(0).at(1), tri_con_pos.at(1).at(1)),
                        tri_con_pos.at(2).at(1)));
                float maxY = clampBtw(std::max(
                        std::max(tri_con_pos.at(0).at(1), tri_con_pos.at(1).at(1)),
                        tri_con_pos.at(2).at(1)));

                // Z-zag, top-left to bottom-right
                // TODO : boundary problems
                for (auto h_ix = static_cast<std::size_t>((1.f - maxY) / delta_y);
                     h_ix < static_cast<std::size_t>((1.f - minY) / delta_y); ++h_ix) {
                    for (auto w_ix = static_cast<std::size_t>((minX + 1.f) / delta_x);
                         w_ix < static_cast<std::size_t>((maxX + 1.f) / delta_x); ++w_ix) {
                        float x_c_coord = -1.f + static_cast<float>(w_ix) * delta_x;
                        float y_c_coord = 1.f - static_cast<float>(h_ix) * delta_y;

                        if (withInTriangle(tri_con_pos, x_c_coord, y_c_coord)) {
                            auto [z, alpha, beta, gamma] = invBarycentric(tri_cam_pos, tri_con_pos, x_c_coord,
                                                                          y_c_coord);
                            if (z > depthBuffer.at(h_ix, w_ix)) {
                                depthBuffer.at(h_ix, w_ix) = z;
                            }
                        }
                    }
                }
            }
        }
        depthBuffer.output("../test/dout.ppm");
    }

    bool Scene::withInTriangle(const std::array<mr::Vector<4, float>, 3> &tri_pos, float x, float y) {
        std::array<mr::Vector<2, float>, 3> tri_pos_2d;
        std::transform(tri_pos.begin(), tri_pos.end(), tri_pos_2d.begin(),
                       [](const mr::Vector<4, float> &v) -> mr::Vector<2, float> {
                           return mr::Vector<2, float>{v.at(0), v.at(1)} / v.at(3);
                       });
        bool c[3];
        mr::Vector<2, float> peek_vec{x, y};
        for (std::size_t i = 0; i < 3; ++i) {
            c[i] = mr::Vector<2, float>::cross(tri_pos_2d.at((i + 1) % 3) - tri_pos_2d.at(i),
                                               peek_vec - tri_pos_2d.at(i)) > 0;
        }
        return (c[0] && c[1] && c[2]) || (!c[0] && !c[1] && !c[2]);
    }

    std::tuple<float, float, float, float>
    Scene::invBarycentric(const std::array<mr::Vector<4, float>, 3> &real_tri,
                          const std::array<mr::Vector<4, float>, 3> &proj_tri,
                          float x, float y) {
//        float x1 = proj_tri.at(1).at(0) - proj_tri.at(0).at(0),
//                y1 = proj_tri.at(1).at(1) - proj_tri.at(0).at(1),
//                x2 = proj_tri.at(2).at(0) - proj_tri.at(0).at(0),
//                y2 = proj_tri.at(2).at(1) - proj_tri.at(0).at(1);
//        float size = std::abs(x1 * y2 - x2 * y1) * .5f;

        float z0 = real_tri.at(0).at(2),
                z1 = real_tri.at(1).at(2),
                z2 = real_tri.at(2).at(2);
        float ap = ((x - proj_tri.at(2).at(0)) * (proj_tri.at(1).at(1) - proj_tri.at(2).at(1)) -
                    (proj_tri.at(1).at(0) - proj_tri.at(2).at(0)) * (y - proj_tri.at(2).at(1))) /
                   ((proj_tri.at(0).at(0) - proj_tri.at(2).at(0)) * (proj_tri.at(1).at(1) - proj_tri.at(2).at(1)) -
                    (proj_tri.at(1).at(0) - proj_tri.at(2).at(0)) * (proj_tri.at(0).at(1) - proj_tri.at(2).at(1)));
        float bp = ((x - proj_tri.at(2).at(0)) - (proj_tri.at(0).at(0) - proj_tri.at(2).at(0)) * ap) /
                   (proj_tri.at(1).at(0) - proj_tri.at(2).at(0));
        float gp = 1 - ap - bp;
        float z = 1 / (ap / z0 +
                       bp / z1 +
                       gp / z2);
        return {z,
                z0 * ap,
                z1 * bp,
                z2 * gp
        };
    }

} // mr