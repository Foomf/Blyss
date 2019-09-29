#pragma once

#include <vector>
#include <cstdint>

#include "cell.hpp"

namespace blyss::server
{
    class map
    {
        std::vector<std::vector<cell>> cells_;

        std::int32_t width_;
        std::int32_t height_;

        void init_cells();

    public:
        map(std::int32_t width, std::int32_t height);
    };
}