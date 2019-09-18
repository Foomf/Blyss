#include "texture_map.hpp"

texture_map::texture_map(std::int32_t texture_size, std::int32_t image_width, std::int32_t image_height)
    : x_scale_{(double)texture_size / (double)image_width}
    , y_scale_{(double)texture_size / (double)image_height}
{
}

texture_ref texture_map::get_ref(std::int32_t x, std::int32_t y) const
{
    texture_ref ref{};
    ref.top_left = glm::vec2(x_scale_ * x, y_scale_ * (y + 1));
    ref.top_right = glm::vec2(x_scale_ * (x + 1), y_scale_ * (y + 1));
    ref.bottom_left = glm::vec2(x_scale_ * x, y_scale_ * y);
    ref.bottom_right = glm::vec2(x_scale_ * (x + 1), y_scale_ * y);
    return ref;
}
