/** @file hello_world.cpp Example 1
 * http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html
 */

#include "ccurses.hpp"

int main() {
    ccurses::window w;
    w.printw("Hello World !!!");
    w.refresh();
    w.getch();
}
