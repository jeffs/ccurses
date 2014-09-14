/** @file scanw_example.cpp Example 4
 * http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/scanw.html
 */
#include "ccurses.hpp"

#include <string>
#include <vector>

using namespace std::string_literals;

int main() {

    ccurses::screen window;

    int row, col;
    window.getmaxyx(row, col);

    auto mesg = "Enter a string: "s;
    window.mvprintw(row / 2, (col - mesg.size()) / 2, "%s", mesg.c_str());

    std::vector<char> str(80);
    window.getnstr(str.data(), str.size() - 1);

    window.mvprintw(ccurses::lines() - 2, 0, "You Entered: %s", str.data());

    window.getch();
}
