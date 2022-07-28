//
// Created by mine268 on 2022-7-24.
//

#pragma once

#include "Vector.h"
#include "Light.h"

namespace mr {

    /**
     * Point-light
     */
    class PointLight : virtual public Light {

        mr::Vector<3, float> position, intensity;

    public:

        PointLight(const mr::Vector<3, float> &, const mr::Vector<3, float> &);

        float getDistanceTo(const mr::Vector<3, float> &) override;

        mr::Vector<3, float> getIntensityAt(const mr::Vector<3, float> &) override;

        mr::Vector<3, float> getLightDirectionAt(const mr::Vector<3, float> &) override;

    };

} // mr

