#include "ccurses.hpp"

int main() {
    ccurses::screen s;
    s.start_color();
    s.init_pair(1, ccurses::color::cyan, ccurses::color::black);

    ccurses::window w;
    w.printw("A Big string which i didn't care to type fully ");
    w.mvchgat(0, 0, -1, ccurses::a_blink, 1);
    w.getch();
}
