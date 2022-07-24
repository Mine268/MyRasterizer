//
// Created by mine268 on 2022-7-24.
//

#include "ParallelLight.h"

namespace mr {

    ParallelLight::ParallelLight(const Vector<3, float> &dir, const Vector<3, float> &ins)
            : Light{}, direction{dir.normalization()}, intensity{ins} {}

    mr::Vector<3, float> ParallelLight::getIntensityAt(const Vector<3, float> &) {
        return direction;
    }

    mr::Vector<3, float> ParallelLight::getLightDirectionAt(const Vector<3, float> &) {
        return intensity;
    }

} // mr