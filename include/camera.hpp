#pragma once

#include <vector>
#include <tuple>
#include <Eigen/Dense>

// 相机类
class camera {
    friend class scene;

    // 相机的位姿
    Eigen::Vector3f position, gaze, up;
    // 相机的观测范围
    float near{}, far{};
    // 图像像素分辨率，和每个像素长度在世界空间中对应的长度
    std::size_t res_x{}, res_y{};
    float pixel_size{};

    Eigen::Matrix4f cam_mat;
    Eigen::Matrix4f persp_mat;
    Eigen::Matrix4f orth_mat;
    Eigen::Matrix4f vp_mat;

public:
    camera(Eigen::Vector3f&&, Eigen::Vector3f&&, Eigen::Vector3f&&,
           float, float, float, std::size_t, std::size_t);

    std::tuple<std::size_t, std::size_t>
        get_image_size() const;
    Eigen::Matrix4f get_camera_mat() const;
    Eigen::Matrix4f get_perspective_mat() const;
    Eigen::Matrix4f get_orthogonal_mat() const;
    Eigen::Matrix4f get_viewport_mat() const;
};
