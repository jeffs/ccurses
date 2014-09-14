#include "ccurses.hpp"

int main() {
    ccurses::screen win;
    ccurses::update up(&win);
    up.printw("Hello World !!!");
    up.refresh();
    win.getch();
}
