/** @file scanw_example.cpp Example 4
 * http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/scanw.html
 */
#include "ccurses.hpp"

#include <string>
#include <vector>

using namespace std::string_literals;

int main() {
    ccurses::window w;

    int row, col;
    w.getmaxyx(row, col);

    auto mesg = "Enter a string: "s;
    w.mvprintw(row / 2, (col - mesg.size()) / 2, "%s", mesg.c_str());

    std::vector<char> str(80);
    w.getnstr(str.data(), str.size() - 1);

    ccurses::screen s;
    w.mvprintw(s.lines() - 2, 0, "You Entered: %s", str.data());

    w.getch();
}
