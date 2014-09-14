#include "ccurses.hpp"

int main() {
    ccurses::screen win;
    win.printw("Hello World !!!");
    win.refresh();
    win.getch();
}
