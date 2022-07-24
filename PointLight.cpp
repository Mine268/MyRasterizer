//
// Created by mine268 on 2022-7-24.
//

#include "PointLight.h"

namespace mr {

    PointLight::PointLight(const Vector<3, float> &p, const Vector<3, float> &i)
            : Light{}, position{p.normalization()}, intensity{i} {}

    mr::Vector<3, float> PointLight::getIntensityAt(const Vector<3, float> &) {
        return intensity;
    }

    mr::Vector<3, float> PointLight::getLightDirectionAt(const Vector<3, float> &p) {
        return (p - position).normalization();
    }


} // mr