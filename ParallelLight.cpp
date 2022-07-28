//
// Created by mine268 on 2022-7-24.
//

#include "ParallelLight.h"

namespace mr {

    ParallelLight::ParallelLight(const Vector<3, float> &dir, const Vector<3, float> &ins, const Vector<3, float> &pos)
            : Light{}, direction{dir.normalization()}, intensity{ins}, position{pos} {}

    mr::Vector<3, float> ParallelLight::getIntensityAt(const Vector<3, float> &) {
        return direction;
    }

    mr::Vector<3, float> ParallelLight::getLightDirectionAt(const Vector<3, float> &) {
        return intensity;
    }

    float ParallelLight::getDistanceTo(const mr::Vector<3, float> &shading_point) {
        return (shading_point - position).length();
    }

} // mr