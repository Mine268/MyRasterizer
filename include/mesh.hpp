#pragma once

#include <vector>
#include <array>
#include <Eigen/Dense>

/**
 * 三角形类，用于表示一个三维空间中的三角形。三角形的点的顺序由传入的三个点的顺序决定
 * 同时也决定了三角形的朝向（右手系）
*/
struct mesh {
    // 按照给定的三个顶点和法向初始化三角形
    mesh(Eigen::Vector3f&&, Eigen::Vector3f&&, Eigen::Vector3f&&,
                Eigen::Vector3f&&, Eigen::Vector3f&&, Eigen::Vector3f&&,
                Eigen::Vector2f&&, Eigen::Vector2f&&, Eigen::Vector2f&&,
                Eigen::Vector3f&&, Eigen::Vector3f&&, Eigen::Vector3f&&,
                float, float, float, int);
    mesh(const mesh&) = default;
    mesh(mesh&&) = default;

    float size() const;
    
    // 三角形的三个顶点
    std::array<Eigen::Vector3f, 3> vertex;
    // 三角形的三个法向量
    std::array<Eigen::Vector3f, 3> norm;
    // 三角形的材质坐标
    std::array<Eigen::Vector2f, 3> texture_coord;
    // 材质参数
    Eigen::Vector3f Ka, Kd, Ks;
    float Ns, Ni, d;
    int illum;
};


// mesh 组成的 vector 作为 mesh 对象使用
using mesh_object = std::vector<mesh>;
