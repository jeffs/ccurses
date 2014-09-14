#include "ccurses.hpp"

#include <ncurses.h>

#include <string>

namespace ccurses {

struct {

    int operator[](a key) const {
        assert(a::bold == key);
        return A_BOLD;
    }

} const attr_map{};

int key_f(int i) { return KEY_F(i); }

void noecho() { if (ERR == ::noecho()) throw "noecho: ERR"; }

void raw() { if (ERR == ::raw()) throw "raw: ERR"; }

// class screen

#define W (WINDOW*)m_window

int screen::getch_() { // getch is a macro
    int r = wgetch(W);
    if (ERR == r) throw "getch: ERR";
    return r;
}

screen::screen(): m_window(initscr()) {
    if (!m_window) throw "initscr: ERR";
    assert(m_window == stdscr);
}

screen::~screen() {
    int r = endwin();
    assert(ERR != r);
}

void screen::attroff_(a attr) {
    if (ERR == wattroff(W, attr_map[attr]))
        throw "wattroff: ERR; attr = " + std::to_string((int)attr);
}

void screen::attron_(a attr) {
    if (ERR == wattron(W, attr_map[attr]))
        throw "wattron: ERR; attr = " + std::to_string((int)attr);
}

void screen::keypad(bool bf) {
    int r = ::keypad(W, bf ? TRUE : FALSE);
    if (ERR == r) throw "keypad: ERR; bf = " + std::to_string(bf);
}

void screen::refresh() {
    if (ERR == wrefresh(W)) throw "refresh: ERR";
}

void screen::printw(const char* fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    int r = ::vw_printw(W, fmt, argp);
    va_end(argp);
    if (ERR == r) throw "wprintw: ERR";
}

#undef W

// class update

update::~update() try {
    refresh();
} catch (...) {
    assert(false);
}

}
