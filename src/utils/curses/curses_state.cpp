#include "utils/curses/curses_state.hpp"

#include <curses.h>

#include "utils/curses/window.hpp"

namespace blyss::utils::curses
{
    curses_state::curses_state()
    {
        stdscr_ = initscr();
        if (stdscr_)
        {
            clear();
            noecho();
            cbreak();
        }
    }

    curses_state::~curses_state()
    {
        endwin();
    }

    bool curses_state::is_success() const
    {
        return stdscr_ != nullptr;
    }

    void curses_state::refresh() const
    {
        ::refresh();
    }

    std::shared_ptr<window> curses_state::make_window(std::int32_t nlines, std::int32_t ncols, std::int32_t begin_y, std::int32_t begin_x)
    {
        return std::make_shared<window>(shared_from_this(), nlines, ncols, begin_y, begin_x);
    }

    std::int32_t curses_state::get_width() const
    {
        return getmaxx(stdscr_);
    }


}