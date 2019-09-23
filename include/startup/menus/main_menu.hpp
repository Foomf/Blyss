#pragma once

#include <memory>

#include "curses_state.hpp"

namespace blyss::startup::menus
{
    class main_menu
    {
        std::shared_ptr<curses_state> curses_;

    public:
        main_menu(std::shared_ptr<curses_state> curses);

        void show();
    };
}