#include "startup/menus/main_menu.hpp"

#include <curses.h>

namespace blyss::startup::menus
{
    main_menu::main_menu(std::shared_ptr<curses_state> curses)
        : curses_{std::move(curses)}
    {
    }


    void main_menu::show()
    {
        char mesg[] = "Enter a string: ";		/* message to be appeared on the screen */
        char str[80];
        int row, col;				/* to store the number of rows and *
                            * the number of colums of the screen */
        getmaxyx(stdscr, row, col);		/* get the number of rows and columns */
        mvprintw(row / 2, (col - strlen(mesg)) / 2, "%s", mesg);
        /* print the message at the center of the screen */
        getstr(str);
        mvprintw(LINES - 2, 0, "You Entered: %s", str);
        getch();
    }

}