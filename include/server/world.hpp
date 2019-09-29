#pragma once

#include <map>
#include <string>
#include <memory>

#include "map.hpp"

namespace blyss::server
{
    class world
    {
        std::map<std::string, std::unique_ptr<map>> maps_;

    public:
        world();

        void add_map(const std::string& name, std::unique_ptr<map> map);
    };
}