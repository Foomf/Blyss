#include "texture_map.hpp"

texture_map::texture_map(std::int32_t texture_size, std::int32_t image_width, std::int32_t image_height)
    : x_scale_{(double)texture_size / (double)image_width}
    , y_scale_{(double)texture_size / (double)image_height}
{
}

texture_ref texture_map::get_ref(std::int32_t x, std::int32_t y)
{
    texture_ref ref{};
    ref.x = x;
    ref.y = y;
    ref.x_scale = x_scale_;
    ref.y_scale = y_scale_;
    return ref;
}
