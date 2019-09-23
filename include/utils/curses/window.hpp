#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "utils/curses/curses_state.hpp"

struct _win;

namespace blyss::utils::curses
{
    class window
    {
        //using curses_window_ptr = std::unique_ptr<_win, void(*)(const _win)>;
        //using curses_window_ptr = std::unique_ptr<WINDOW>;

        std::shared_ptr<curses_state> curses_state_;

        _win* win_ptr_;

    public:
        window(std::shared_ptr<curses_state> curses_state, std::int32_t nlines, std::int32_t ncols, std::int32_t begin_y, std::int32_t begin_x);

        void move_and_print(std::int32_t y, std::int32_t x, const std::string& str) const;

        std::int32_t get_char();
    };
}