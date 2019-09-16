#pragma once

#include <cstdint>

class texture_map
{
    double x_scale_;
    double y_scale_;

public:
    texture_map(std::int32_t texture_size, std::int32_t image_width, std::int32_t image_height);
};