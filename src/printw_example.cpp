/** @file printw_example.cpp Example 3
 * http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/printw.html
 */

#include "ccurses.hpp"

#include <string>

using namespace std::string_literals;

int main() {
    ccurses::window w;

    int row, col;
    w.getmaxyx(row, col);

    auto mesg = "Just a string"s;
    w.mvprintw(row / 2, (col - mesg.size()) / 2, "%s", mesg.c_str());

    w.mvprintw(row - 2, 0,
            "This screen has %d rows and %d columns.\n", row, col);

    w.printw("Try resizing your window and then run this program again.");

    w.refresh();

    w.getch();
}
