//
// Created by mine268 on 2022-7-22.
//

#include <cassert>

#include "Camera.h"

namespace mr {
    Camera::Camera(float w, float h, float asp,
                   const Vector<3, float> &pos,
                   const Vector<3, float> &dir,
                   const Vector<3, float> &up)
            : width{w}, height{h}, aspectRatio{asp},
              position{pos}, direction{dir.normalization()}, upperSide{up.normalization()} {
        assert(w > 0 && h > 0 && asp > 0);
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

} // mr
