#include "startup/menus/main_menu.hpp"

#include <curses.h>

namespace blyss::startup::menus
{
    const char* banner_text =
        "  ____  _               \n"
        " |  _ \\| |              \n"
        " | |_) | |_   _ ___ ___ \n"
        " |  _ <| | | | / __/ __|\n"
        " | |_) | | |_| \\__ \\__ \\\n"
        " |____/|_|\\__, |___/___/\n"
        "           __/ |        \n"
        "          |___/         \n";

    main_menu::main_menu(std::shared_ptr<curses_state> curses)
        : banner_{curses->make_window(10, 30, 0, 0)}
        , win_{curses->make_window(10, 30, 10, 10)}
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
        win_->use_keypad();
    }

    void main_menu::show()
    {
        banner_->center();
        banner_->move_and_print(0, 0, banner_text);
        banner_->refresh();

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
        auto x = 2;
        auto y = 2;

        for (auto ii = 0; ii < menu_options_.size(); ++ii)
        {
            if (choice_ == ii)
            {
                win_->enable_reverse();
                win_->move_and_print(y, x, menu_options_[ii]);
                //mvwprintw(curses_->stdscr(), y, x, "%s", menu_options_[ii].c_str());
                win_->disable_reverse();
            }
            else
            {
                win_->move_and_print(y, x, menu_options_[ii]);
                //mvwprintw(curses_->stdscr(), y, x, "%s", menu_options_[ii].c_str());
            }
            ++y;
        }

        win_->refresh();
    }


}