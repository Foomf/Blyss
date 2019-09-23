#pragma once

#include <curses.h>

namespace blyss::utils::curses
{
    class curses_state
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
        [[nodiscard]] WINDOW* stdscr() const;
        void refresh() const;
    };
}
