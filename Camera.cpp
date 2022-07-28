//
// Created by mine268 on 2022-7-22.
//

#include <cassert>

#include "Camera.h"

namespace mr {
    Camera::Camera(std::size_t w, std::size_t h,
                   float n, float f, float asp,
                   const Vector<3, float> &pos,
                   const Vector<3, float> &dir,
                   const Vector<3, float> &up)
            : width{w}, height{h}, near{n}, far{f}, aspectRatio{asp},
              position{pos}, direction{dir.normalization()}, upperSide{up.normalization()} {
        assert(w > 0 && h > 0 && n < 0 && n > f && asp > 0);
    }

    float Camera::getDistance() const {
        return height / (aspectRatio);
    }

    mr::Matrix<4, 4, float> Camera::getCameraMatrix() const {
        return mr::Matrix<4, 4, float>{
                upperSide.at(2) * direction.at(1) - upperSide.at(1) * direction.at(2), upperSide.at(0),
                -direction.at(0), position.at(0),
                upperSide.at(0) * direction.at(2) - upperSide.at(2) * direction.at(0), upperSide.at(1),
                -direction.at(1), position.at(1),
                upperSide.at(1) * direction.at(0) - upperSide.at(0) * direction.at(1), upperSide.at(2),
                -direction.at(2), position.at(2),
                0, 0, 0, 1
        }.inverse();
    }

    mr::Matrix<4, 4, float> Camera::getProjMat() const {
        return mr::Matrix<4, 4, float>{
                near, 0, 0, 0,
                0, near, 0, 0,
                0, 0, near + far, near * far,
                0, 0, -1, 0
        };
    }

    mr::Matrix<4, 4, float> Camera::getOrthMat() const {
        float y_span = -near * aspectRatio,
                z_span = near - far,
                x_span = static_cast<float>(width) / static_cast<float>(height) * y_span;
        return mr::Matrix<4, 4, float>{
                2 / x_span, 0, 0, 0,
                0, 2 / y_span, 0, 0,
                0, 0, 2 / z_span, (near + far) / z_span,
                0, 0, 0, 1
        };
    }

    mr::Matrix<4, 4, float> Camera::getViewPortMat() const {
        return mr::Matrix<4, 4, float>{
                static_cast<float>(width) / 2.f, 0, 0, static_cast<float>(width - 1) / 2.f,
                0, static_cast<float>( height) / 2.f, 0, static_cast<float>(height - 1) / 2.f,
                0, 0, 1, 0,
                0, 0, 0, 1
        };
    }

} // mr
