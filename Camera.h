//
// Created by mine268 on 2022-7-22.
//

#pragma once

#include "Vector.h"
#include "Matrix.h"

namespace mr {

    /**
     * Camera profile
     */
    struct Camera {
        // width & height of the image
        float width{}, height{};

        // distance between the camera & image plane defined by the ratio
        // height / distance
        float aspectRatio;

        mr::Vector<3, float> position{}, // position of the camera
        direction{}, // direction of the camera
        upperSide{}; // upper direction of the camera

        // construct
        Camera(float w, float h, float asp,
               const mr::Vector<3, float> &pos,
               const mr::Vector<3, float> &dir,
               const mr::Vector<3, float> &up);

        /**
         * Get the distance between camera and image plane.
         * @return distance
         */
        float getDistance() const;

        /**
         * Get the transformation putting camera at origin.
         * @return the matrix
         */
        mr::Matrix<4, 4, float> getCameraMatrix() const;

        mr::Matrix<4, 4, float> getICameraMatrix() const;
    };

} // mr
