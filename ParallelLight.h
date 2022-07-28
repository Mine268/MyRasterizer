//
// Created by mine268 on 2022-7-24.
//

#pragma once

#include "Light.h"
#include "Vector.h"

namespace mr {

    /**
     * Parallel light
     */
    class ParallelLight : virtual public Light {

        mr::Vector<3, float> direction, intensity, position;

    public:

        ParallelLight(const mr::Vector<3, float> &, const mr::Vector<3, float> &, const mr::Vector<3, float> &);

        float getDistanceTo(const mr::Vector<3, float> &) override;

        mr::Vector<3, float> getIntensityAt(const mr::Vector<3, float> &) override;

        mr::Vector<3, float> getLightDirectionAt(const mr::Vector<3, float> &) override;

    };

} // mr
