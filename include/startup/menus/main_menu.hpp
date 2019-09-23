#pragma once

#include <memory>
#include <vector>
#include <string>
#include <cstdint>

#include "curses_state.hpp"

namespace blyss::startup::menus
{
    class main_menu
    {
        std::shared_ptr<curses_state> curses_;
        std::vector<std::string> menu_options_;
        std::int32_t choice_;

        void print_menu() const;

    public:
        main_menu(std::shared_ptr<curses_state> curses);

        void show();
    };
}