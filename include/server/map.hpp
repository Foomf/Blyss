#pragma once

#include <vector>
#include <memory>
#include <cstdint>

#include "cell.hpp"

namespace blyss::server
{
    class map
    {
        std::vector<std::vector<std::unique_ptr<cell>>> cells_;

        std::int32_t width_;
        std::int32_t height_;

        void init_cells();

    public:
        map(std::int32_t width, std::int32_t height);
    };
}