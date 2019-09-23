#include "utils/curses/window.hpp"

#include "utils/curses/curses_state.hpp"

#include <curses.h>

namespace blyss::utils::curses
{
    window::window(std::shared_ptr<curses_state> curses_state, std::int32_t nlines, std::int32_t ncols, std::int32_t begin_y, std::int32_t begin_x)
        : curses_state_{std::move(curses_state)}
        , win_ptr_{curses_window_ptr(newwin(nlines, ncols, begin_y, begin_x), delwin)}
    {
    }

    void window::move_and_print(std::int32_t y, std::int32_t x, const std::string& str) const
    {
        ::mvwprintw(win_ptr_.get(), y, x, str.c_str());
    }

    std::int32_t window::get_char() const
    {
        return wgetch(win_ptr_.get());
    }

    void window::enable_reverse() const
    {
        wattron(win_ptr_.get(), A_REVERSE);
    }

    void window::disable_reverse() const
    {
        wattroff(win_ptr_.get(), A_REVERSE);
    }

    void window::refresh() const
    {
        wrefresh(win_ptr_.get());
    }

    void window::use_keypad() const
    {
        keypad(win_ptr_.get(), true);
    }

    void window::box() const
    {
        ::box(win_ptr_.get(), 0, 0);
    }

    void window::center() const
    {
        const auto terminal_width = curses_state_->get_width();
        const auto window_width = getmaxx(win_ptr_.get());
        const auto window_y = getbegx(win_ptr_.get());
        mvwin(win_ptr_.get(), window_y, terminal_width / 2 - window_width / 2);
    }

    std::int32_t window::get_height() const
    {
        return getmaxy(win_ptr_.get());
    }

    void window::move_y(std::int32_t y) const
    {
        const auto window_x = getbegx(win_ptr_.get());
        mvwin(win_ptr_.get(), y, window_x);
    }


}
