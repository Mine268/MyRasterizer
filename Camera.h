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
        std::size_t width{}, height{};

        // near & far
        float near, far;

        // distance between the camera & image plane defined by the ratio
        // height / distance
        float aspectRatio;

        mr::Vector<3, float> position{}, // position of the camera
        direction{}, // direction of the camera
        upperSide{}; // upper direction of the camera

        // construct
        Camera(std::size_t w, std::size_t h,
               float n, float f, float asp,
               const mr::Vector<3, float> &pos,
               const mr::Vector<3, float> &dir,
               const mr::Vector<3, float> &up);

        /**
         * Get the transformation putting camera at origin.
         * @return the matrix
         */
        mr::Matrix<4, 4, float> getCameraMatrix() const;

        /**
         * Get the projection matrix
         * @return proj matrix
         */
        mr::Matrix<4, 4, float> getProjMat() const;

        /**
         * Get the orth. matrix
         * @return the matrix
         */
        mr::Matrix<4, 4, float> getOrthMat() const;

        /**
         * Get the viewport trans. mat.
         * @return viewport trans. mat.
         */
        mr::Matrix<4, 4, float> getViewPortMat() const;
    };

} // mr
