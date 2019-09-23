#include "startup/menus/main_menu.hpp"

#include <curses.h>

namespace blyss::startup::menus
{
    main_menu::main_menu(std::shared_ptr<curses_state> curses)
        : win_{/*curses->make_window(10, 30, 0, 0)*/}
        , curses_{std::move(curses)}
        , menu_options_{
            "Play Single Player",
            "Connect To Server",
            "Run Dedicated Server",
            "Help",
            "Quit"
        }
        , choice_{0}
    {
    }

    void main_menu::show()
    {
        //keypad(curses_->stdscr(), true);
        win_->move_and_print(0, 0, "Use arrow keys to go up and down, press enter to select a choice");
        curses_->refresh();
        print_menu();
        auto done = false;
        while(!done)
        {
            auto c = win_->get_char();
            switch(c)
            {
            case KEY_UP:
                if (choice_ <= 0)
                {
                    choice_ = menu_options_.size() - 1;
                }
                else
                {
                    --choice_;
                }
                break;
            case KEY_DOWN:
                if (choice_ >= menu_options_.size() - 1)
                {
                    choice_ = 0;
                }
                else
                {
                    ++choice_;
                }
                break;
            default:
                done = true;
                break;
            }

            print_menu();
        }
        clrtoeol();
        refresh();

    }

    void main_menu::print_menu() const
    {
        //auto x = 2;
        //auto y = 2;

        //for (auto ii = 0; ii < menu_options_.size(); ++ii)
        //{
        //    if (choice_ == ii)
        //    {
        //        wattron(curses_->stdscr(), A_REVERSE);
        //        mvwprintw(curses_->stdscr(), y, x, "%s", menu_options_[ii].c_str());
        //        wattroff(curses_->stdscr(), A_REVERSE);
        //    }
        //    else
        //    {
        //        mvwprintw(curses_->stdscr(), y, x, "%s", menu_options_[ii].c_str());
        //    }
        //    ++y;
        //}

        //wrefresh(curses_->stdscr());
    }


}