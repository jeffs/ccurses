/** @file hello_world.cpp Example 1
 * http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html
 */

#include "ccurses.hpp"

int main() {
    ccurses::screen win;
    win.printw("Hello World !!!");
    win.refresh();
    win.getch();
}
