#pragma once

#include <memory>
#include <cstdint>

#include <curses.h>

//#include "utils/curses/window.hpp"


namespace blyss::utils::curses
{
    class window;

    class curses_state : public std::enable_shared_from_this<curses_state>
    {
        WINDOW* stdscr_;

    public:
        curses_state();
        ~curses_state();

        curses_state(const curses_state&) = delete;
        curses_state(curses_state&&) = delete;
        curses_state& operator=(const curses_state&) = delete;
        curses_state& operator=(curses_state&&) = delete;

        [[nodiscard]] bool is_success() const;
        void refresh() const;
        std::shared_ptr<window> make_window(std::int32_t nlines, std::int32_t ncols, std::int32_t begin_y, std::int32_t begin_x);
    };
}
