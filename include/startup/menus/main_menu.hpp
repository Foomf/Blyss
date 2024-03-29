#pragma once

#include <memory>
#include <vector>
#include <string>
#include <cstdint>

#include "utils/curses/curses_state.hpp"
#include "utils/curses/window.hpp"

namespace blyss::startup::menus
{
    using namespace utils::curses;

    class main_menu
    {
        std::shared_ptr<window> banner_;
        std::shared_ptr<window> menu_win_;
        std::vector<std::string> menu_options_;
        std::int32_t choice_;

        void print_menu() const;

    public:
        main_menu(const std::shared_ptr<curses_state>& curses);

        void show();
    };
}