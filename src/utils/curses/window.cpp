#include "utils/curses/window.hpp"

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

    std::int32_t window::get_char()
    {
        return wgetch(win_ptr_.get());
    }


}
