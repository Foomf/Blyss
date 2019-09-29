#include "server/map.hpp"

namespace blyss::server
{
    map::map(std::int32_t width, std::int32_t height)
        : cells_{width}
        , width_{width}
        , height_{height}
    {
        init_cells();
    }

    void map::init_cells()
    {
        for(auto x = 0; x < width_; ++x)
        {
            cells_[x].reserve(height_);
            for (auto y = 0; y < height_; ++y)
            {
                cells_[x].emplace_back();
            }
        }
    }

}