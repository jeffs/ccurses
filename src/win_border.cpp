/** @file win_border.cpp Example 7
 * http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/windows.html
 */

#include "ccurses.hpp"

ccurses::window* create_newwin(int height, int width, int starty, int startx) {
    auto local_win = new ccurses::window(height, width, starty, startx);
    local_win->box(0, 0);
    local_win->refresh();
    return local_win;
}

void destroy_win(ccurses::window* local_win) {
    local_win->border(' ', ' ', ' ',' ',' ',' ',' ',' ');
    local_win->refresh();
    delete local_win;
}

int main(int argc, char *argv[]) {

    ccurses::screen scr;
    scr.cbreak();

    ccurses::window win;
    win.keypad();

    int height = 3;
    int width = 10;
    int starty = (scr.lines() - height) / 2;
    int startx = (scr.cols() - width) / 2;
    win.printw("Press F1 to exit");
    win.refresh();

    auto my_win = create_newwin(height, width, starty, startx);

    for (int ch; (ch = win.getch()) != scr.key_f(1);) {
        if (ch == ccurses::key_left) {
            destroy_win(my_win);
            my_win = create_newwin(height, width, starty, --startx);
        } else if (ch == ccurses::key_right) {
            destroy_win(my_win);
            my_win = create_newwin(height, width, starty, ++startx);
        } else if (ch == ccurses::key_up) {
            destroy_win(my_win);
            my_win = create_newwin(height, width, --starty, startx);
        } else if (ch == ccurses::key_down) {
            destroy_win(my_win);
            my_win = create_newwin(height, width, ++starty, startx);
        }
    }
}
