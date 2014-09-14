#include "ccurses.hpp"

#include <ncurses.h>

#include <cassert>
#include <string>

namespace ccurses {

struct {

    int operator[](a key) const {
        assert(a::bold == key);
        return A_BOLD;
    }

} const attr_map{};

int detail::getch_() {
    int r = getch(); // getch is a macro
    if (ERR == r) throw "getch: ERR";
    return r;
}

int key_f(int i) { return KEY_F(i); }

void noecho() { if (ERR == ::noecho()) throw "noecho: ERR"; }

void raw() { if (ERR == ::raw()) throw "raw: ERR"; }

// class screen

screen::screen(): m_window(initscr()) {
    if (!m_window) throw "initscr: ERR";
}

screen::~screen() { int r = endwin(); assert(ERR != r); }

void screen::keypad(bool bf) {
    int r = ::keypad((WINDOW*)m_window, bf ? TRUE : FALSE);
    if (ERR == r) throw "keypad: ERR; bf = " + std::to_string(bf);
}

void screen::wprintw(const char* fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    int r = ::vw_printw((WINDOW*)m_window, fmt, argp);
    va_end(argp);
    if (ERR == r) throw "wprintw: ERR";
}

// class update

void update::attroff_(a attribute) {
    int r = attroff(attr_map[attribute]);
    if (ERR == r)
        throw "attroff: ERR; attribute = " + std::to_string((int)attribute);
}

void update::attron_(a attribute) {
    int r = attron(attr_map[attribute]);  // attron is a macro
    if (ERR == r)
        throw "attron: ERR; attribute = " + std::to_string((int)attribute);
}

update::~update() { int r = ::refresh(); assert(ERR != r); }

void update::refresh() { if (ERR == ::refresh()) throw "refresh: ERR"; }

}
