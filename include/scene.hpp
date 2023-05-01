#pragma once

// 场景类，用来组织相机、光照和物体

#include <vector>
#include <memory>

#include "camera.hpp"
#include "light.hpp"
#include "parallel_light.hpp"
#include "world_object.hpp"


struct scene {
    // 所有的光照，因为光照类有继承体系，使用智能指针托管
    std::vector<std::unique_ptr<light>> lights;
    // 所有的相机
    std::vector<camera> cameras;
    // 所有的物体
    std::vector<world_object> objects;

    /**
     * 渲染图片
     * @param cam_ix 渲染图片的相机的编号
     */
    void render(std::size_t cam_ix) const;
};
