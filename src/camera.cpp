#include "../include/camera.hpp"
#include "../include/utils.hpp"

camera::camera(Eigen::Vector3f &&pos, Eigen::Vector3f &&gaze, Eigen::Vector3f &&up, float n, float f, float ps,
               std::size_t nx, std::size_t ny) :
        position(std::forward<Eigen::Vector3f>(pos)), gaze(std::forward<Eigen::Vector3f>(gaze)),
        up(std::forward<Eigen::Vector3f>(up)), near(n), far(f), pixel_size(ps), res_x(nx), res_y(ny) {
    // 计算相机变换矩阵
    // 首先将确保 up 与 gaze 垂直
    this->gaze.normalize(); this->up.normalize();
    this->up -= this->gaze * (this->up.dot(this->gaze));
    this->up.normalize();
    // 计算相机坐标系的基
    Eigen::Vector3f uz(-this->gaze);
    Eigen::Vector3f uy(this->up);
    Eigen::Vector3f ux(uy.cross(uz));
    // 填写矩阵并求逆
    this->cam_mat.setZero();
    this->cam_mat.topRows(3) << ux, uy, uz, this->position;
    this->cam_mat(3, 3) = 1;
    this->cam_mat = this->cam_mat.inverse().eval();

    // 计算投影矩阵
    this->persp_mat.setZero();
    this->persp_mat(0, 0) = this->persp_mat(1, 1) = near;
    this->persp_mat(3, 2) = 1;
    this->persp_mat(2, 2) = near + far;
    this->persp_mat(2, 3) = -near * far;

    // 计算正交投影矩阵
    auto image_width_in_world = static_cast<float>(res_x) * this->pixel_size;
    auto image_height_in_world = static_cast<float>(res_y) * this->pixel_size;
    this->orth_mat.setZero();
    this->orth_mat(0, 0) = 2 / image_width_in_world;
    this->orth_mat(1, 1) = 2 / image_height_in_world;
    this->orth_mat(2, 2) = 2 / (near - far);
    this->orth_mat(3, 3) = 1;
    this->orth_mat(2, 3) = -(near + far) / (near - far);

    // 计算视口变换
    this->vp_mat.setZero();
    this->vp_mat(0, 0) = static_cast<float>(res_x) * .5f;
    this->vp_mat(1, 1) = static_cast<float>(res_y) * .5f;
    this->vp_mat(2, 2) = 1;
    this->vp_mat(3, 3) = 1;
    this->vp_mat(0, 3) = static_cast<float>(res_x - 1) * .5f;
    this->vp_mat(1, 3) = static_cast<float>(res_y - 1) * .5f;
}

Eigen::Matrix4f camera::get_camera_mat() const {
    return this->cam_mat;
}

Eigen::Matrix4f camera::get_perspective_mat() const {
    return this->persp_mat;
}

Eigen::Matrix4f camera::get_orthogonal_mat() const {
    return this->orth_mat;
}

Eigen::Matrix4f camera::get_viewport_mat() const {
    return this->vp_mat;
}

std::tuple<std::size_t, std::size_t> camera::get_image_size() const {
    return std::make_tuple(
            this->res_y, this->res_x);
}

