#include "../include/stb_image_write.hpp"

#include "../include/scene.hpp"
#include "../include/image.hpp"
#include "../include/utils.hpp"


void scene::render(std::size_t cam_ix) const {
    auto [height, width] = cameras[cam_ix].get_image_size();
    // 构造最终存储图像的对象
    image output{height, width}; output.clear();
    // 深度图像
    image depth{height, width}; depth.clear(255);
    // 从相机中读取变换参数
    auto cam_mat = cameras[cam_ix].get_camera_mat();
    auto perp_mat = cameras[cam_ix].get_perspective_mat();
    auto orth_mat = cameras[cam_ix].get_orthogonal_mat();
    auto vp_mat = cameras[cam_ix].get_viewport_mat();

    Eigen::Matrix4f c2p_mat = vp_mat * orth_mat * perp_mat;
    Eigen::Matrix4f w2p_mat = c2p_mat * cam_mat;

    // 遍历每一个物体
    for (const auto& object : objects) {
        // 遍历物体上的每个三角形
        for (const auto tri : object) {
            // 将源三角形的所有点送入矩阵便于运算
            Eigen::Matrix<float, 4, 3> raw_point_homo = Eigen::Matrix<float, 4, 3>::Ones();
            raw_point_homo.topRows(3) << tri.vertex[0], tri.vertex[1], tri.vertex[2];
            // 将世界坐标中的点投影到像素空间中，此时坐标还没有非齐次化
            Eigen::Matrix<float, 4, 3> pixel_point_homo = w2p_mat * raw_point_homo;
            // 齐次化坐标
            Eigen::Matrix3f pixel_point = pixel_point_homo.topRows(3);
            for (Eigen::Index i = 0; i < 3; ++i)
                pixel_point(Eigen::all, i) /= pixel_point_homo(3, i);

            float x_min, x_max, y_min, y_max;
            x_min = pixel_point(0, Eigen::all).minCoeff();
            x_max = pixel_point(0, Eigen::all).maxCoeff();
            y_min = pixel_point(1, Eigen::all).minCoeff();
            y_max = pixel_point(1, Eigen::all).maxCoeff();

            // 如果该三角形的所有像素坐标在图像之外，则不渲染这个三角形
            if (x_max < 0 || x_min > static_cast<float>(width) || y_max < 0 || y_min > static_cast<float>(height))
                continue;

            // 像素坐标
            std::size_t h_max = std::min(height - 1, static_cast<std::size_t>(std::ceil(y_max)));
            std::size_t h_min = std::max(static_cast<std::size_t>(0), static_cast<std::size_t>(std::floor(y_min)));
            std::size_t w_max = std::min(width - 1, static_cast<std::size_t>(std::ceil(x_max)));
            std::size_t w_min = std::max(static_cast<std::size_t>(0), static_cast<std::size_t>(std::floor(x_min)));

            // 遍历这个三角形的所有位置
            for (std::size_t h_ix = h_min; h_ix <= h_max; ++h_ix) {
                for (std::size_t w_ix = w_min; w_ix <= w_max; ++w_ix) {
                    // 浮点化的像素坐标
                    auto h_coord = static_cast<float>(h_ix);
                    auto w_coord = static_cast<float>(w_ix);
                    // 像素空间中的重心坐标
                    auto [alpha, beta, gamma] = get_bc_weight(w_coord, h_coord,
                                                              pixel_point({0, 1}, 0),
                                                              pixel_point({0, 1}, 1),
                                                              pixel_point({0, 1}, 2));

                    if (alpha < 0 || beta < 0 || gamma < 0) continue;

                    // 计算真实的深度坐标
                    auto true_depth = 1 /
                            (alpha / tri.vertex[0](2) + beta / tri.vertex[1](2) + gamma / tri.vertex[2](2));
                    // 计算真实的 alpha, beta, gamma
                    alpha *= true_depth / tri.vertex[0](2);
                    beta *= true_depth / tri.vertex[1](2);
                    gamma *= true_depth / tri.vertex[2](2);

//                    auto depth_color = 255.f * cameras[cam_ix].near / true_depth;
                    auto depth_color = -720 * true_depth;

                    depth.at(h_ix, w_ix)[0] = std::min(
                            depth.at(h_ix, w_ix)[0],
                            static_cast<unsigned char>(std::clamp(depth_color, 0.f, 255.f)));
                    depth.at(h_ix, w_ix)[1] = std::min(
                            depth.at(h_ix, w_ix)[1],
                            static_cast<unsigned char>(std::clamp(depth_color, 0.f, 255.f)));
                    depth.at(h_ix, w_ix)[2] = std::min(
                            depth.at(h_ix, w_ix)[2],
                            static_cast<unsigned char>(std::clamp(depth_color, 0.f, 255.f)));
                }
            }
        }
    }
    // TODO: debug
    depth.save_to("depth.bmp");
}
