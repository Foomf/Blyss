#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <functional>

struct _win;

namespace blyss::utils::curses
{
    class curses_state;

    class window
    {
        using curses_window_ptr = std::unique_ptr<_win, std::function<void(_win*)>>;

        std::shared_ptr<curses_state> curses_state_;

        curses_window_ptr win_ptr_;

    public:
        window(std::shared_ptr<curses_state> curses_state, std::int32_t nlines, std::int32_t ncols, std::int32_t begin_y, std::int32_t begin_x);

        void move_and_print(std::int32_t y, std::int32_t x, const std::string& str) const;

        [[nodiscard]] std::int32_t get_char() const;

        void use_keypad() const;

        void enable_reverse() const;

        void disable_reverse() const;

        void refresh() const;

        void box() const;

        void center() const;

        [[nodiscard]] std::int32_t get_height() const;

        void move_y(std::int32_t y) const;
    };
}