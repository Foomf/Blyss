#include "startup/menus/main_menu.hpp"

#include <curses.h>

#include "banner.hpp"

namespace blyss::startup::menus
{
    main_menu::main_menu(const std::shared_ptr<curses_state>& curses)
        : banner_{curses->make_window(10, 30, 0, 0)}
        , menu_win_{curses->make_window(15, 30, 10, 10)}
        , menu_options_{
            "Play Single Player",
            "Connect To Server",
            "Run Dedicated Server",
            "Help",
            "Quit"
        }
        , choice_{0}
    {
        menu_win_->use_keypad();
    }

    void main_menu::show()
    {
        banner_->center();
        banner_->move_and_print(0, 0, banner_text);
        banner_->refresh();

        menu_win_->move_y(banner_->get_height() + 3);
        menu_win_->center();

        print_menu();
        auto done = false;
        while(!done)
        {
            auto c = menu_win_->get_char();
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
                menu_win_->enable_reverse();
                menu_win_->move_and_print(y, x, menu_options_[ii]);
                menu_win_->disable_reverse();
            }
            else
            {
                menu_win_->move_and_print(y, x, menu_options_[ii]);
            }
            y += 2;
        }

        menu_win_->refresh();
    }


}