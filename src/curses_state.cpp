#include "curses_state.hpp"

#include <curses.h>

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

WINDOW* curses_state::stdscr() const
{
    return stdscr_;
}

void curses_state::refresh() const
{
    ::refresh();
}
