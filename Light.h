//
// Created by mine268 on 2022-7-24.
//

#pragma once

#include "Vector.h"

namespace mr {

    /**
     * Light interface
     */
    class Light {

    public:

        Light() = default;

        virtual ~Light() = default;

        virtual float getDistanceTo(const mr::Vector<3, float> &) = 0;

        virtual mr::Vector<3, float> getIntensityAt(const mr::Vector<3, float> &) = 0;

        virtual mr::Vector<3, float> getLightDirectionAt(const mr::Vector<3, float> &) = 0;

    };

} // mr
