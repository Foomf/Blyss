#pragma once

#include <cstdint>

struct texture_ref
{
    std::int32_t x;
    std::int32_t y;
    double x_scale;
    double y_scale;
};