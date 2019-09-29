#include "server/world.hpp"

namespace blyss::server
{
    world::world()
    {
        
    }

    void world::add_map(const std::string& name, std::unique_ptr<map> map)
    {
        maps_.emplace(name, std::move(map));
    }


}