#pragma once

#include <tuple>

#include "../include/mesh.hpp"
#include "../include/OBJ_loader.hpp"


// 将 objloader 的结果转换为自己的 mesh 格式
mesh_object loader_to_mesh_object(const objl::Loader&, std::size_t);


// 非齐次坐标转齐次坐标
Eigen::Vector4f eu2homo(const Eigen::Vector3f& x3d);


// 齐次坐标转非齐次坐标
Eigen::Vector3f homo2eu(const Eigen::Vector4f& x4d);


// 计算三角形的重心坐标
std::tuple<float, float, float>
        get_bc_weight(float x, float y,
                      const Eigen::Vector2f& v1,
                      const Eigen::Vector2f& v2,
                      const Eigen::Vector2f& v3);
