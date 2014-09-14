/** @file printw_example.cpp Example 3
 * http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/printw.html
 */

#include "ccurses.hpp"

#include <string>

using namespace std::string_literals;

int main() {

    ccurses::screen window;

    int row, col;
    window.getmaxyx(row, col);

    auto mesg = "Just a string"s;
    window.mvprintw(row / 2, (col - mesg.size()) / 2, "%s", mesg.c_str());

    window.mvprintw(row - 2, 0,
            "This screen has %d rows and %d columns.\n", row, col);

    window.printw("Try resizing your window and then run this program again.");

    window.refresh();

    window.getch();
}
