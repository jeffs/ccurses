#include "ccurses.hpp"

#include <ncurses.h>

#include <cassert>

namespace ccurses {

screen::screen():
    m_window(initscr()) {
    if (!m_window)
        throw "initscr: ERR";
}

screen::~screen() {
    int r = endwin();
    assert(ERR != r);
}

update::~update() {
    int r = ::refresh();
    assert(ERR != r);
}

void update::getch_() {
    if (ERR == getch()) throw "getch: ERR"; // getch is a macro
}

void update::printw(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int r = ::printw(fmt, args);
    va_end(args);
    if (ERR == r) throw "printw: ERR";
}

void update::refresh() {
    if (ERR == ::refresh()) throw "refresh: ERR";
}

}
