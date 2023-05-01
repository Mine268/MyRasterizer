#pragma once

#include <Eigen/Dense>


// 描述某一点光照信息的结构体
struct light_hit {
    // 照射方向
    Eigen::Vector3f orientation;
    // 颜色
    Eigen::Vector3f color;
    // 强度
    float intensity;
};


struct light {
    /**
     * 光照计算方法，计算该光源在某一点处的光照参数，包括
     * 光线朝向、颜色和强度
     * @param position 需要计算光照参数的位置
     * @return 光照参数结构体
     */
    virtual light_hit evaluate_light(
            const Eigen::Vector3f& position
            ) = 0;
};
