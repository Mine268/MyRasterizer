#pragma once

#include <Eigen/Dense>

#include "../include/light.hpp"

// 平行光

struct parallel_light : public virtual light {
    // 朝向
    Eigen::Vector3f orientation;
    // 颜色，位于 0~1 之间
    Eigen::Vector3f color;
    // 强度
    float intensity;

    /**
     * 查询该光源照射某一点时的光照参数，平行光源强度不衰减，
     *  颜色不变化，朝向不变化
     * @param position 该点的位置
     * @return 光照参数结构体 light_hit
     */
    light_hit evaluate_light(
            const Eigen::Vector3f& position
            ) override;

};
