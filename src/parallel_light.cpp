#include "../include/parallel_light.hpp"


light_hit parallel_light::evaluate_light(const Eigen::Vector3f &position) {
    return light_hit{
        this->orientation,
        this->color,
        intensity
    };
}
