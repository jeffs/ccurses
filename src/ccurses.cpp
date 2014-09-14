#include "ccurses.hpp"

#include <ncurses.h>

#include <array>
#include <string>

using namespace std::string_literals;

using std::to_string;

namespace ccurses {

struct {

    int operator[](attribute attrs) const {
        return (attrs & a_normal     ? A_NORMAL     : 0)
            |  (attrs & a_standout   ? A_STANDOUT   : 0)
            |  (attrs & a_underline  ? A_UNDERLINE  : 0)
            |  (attrs & a_reverse    ? A_REVERSE    : 0)
            |  (attrs & a_blink      ? A_BLINK      : 0)
            |  (attrs & a_dim        ? A_DIM        : 0)
            |  (attrs & a_bold       ? A_BOLD       : 0)
            |  (attrs & a_protect    ? A_PROTECT    : 0)
            |  (attrs & a_invis      ? A_INVIS      : 0)
            |  (attrs & a_altcharset ? A_ALTCHARSET : 0)
            |  (attrs & a_chartext   ? A_CHARTEXT   : 0);
    }

} const attr_map{};

std::array<int, 8> const color_map = {{
    COLOR_BLACK,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN,
    COLOR_WHITE
}};

void init_pair(short pair, color f, color b) {
    ::init_pair(pair, color_map[int(f)], color_map[int(b)]);
}

int key_f(int i) { return KEY_F(i); }

int lines() { return LINES; }

void noecho() { if (ERR == ::noecho()) throw "noecho: ERR"; }

void raw() { if (ERR == ::raw()) throw "raw: ERR"; }

void start_color() { if (ERR == ::start_color()) throw "start_color: ERR"; }

// class screen

#define W (WINDOW*)m_window

void screen::attroff_(attribute attrs) {
    if (ERR == wattroff(W, attr_map[attrs]))
        throw "wattroff: ERR; attrs = " + to_string(attrs.value);
}

void screen::attron_(attribute attrs) {
    if (ERR == wattron(W, attr_map[attrs]))
        throw "wattron: ERR; attrs = " + to_string(attrs.value);
}

int screen::getch_() { // getch is a macro
    int r = wgetch(W);
    if (ERR == r) throw "getch: ERR";
    return r;
}

void screen::getnstr_(char* str, int n) {
    int r = wgetnstr(W, str, n);
    if (ERR == r) throw "getnstr: ERR; n = " + to_string(n);
}

void screen::move_(int y, int x) {
    if (ERR == wmove(W, y, x))
        throw "move: ERR; y = " + to_string(y) + ", x = " + to_string(x);
}

void screen::mvchgat_(
        int         y,
        int         x,
        int         n,
        attribute   attrs,
        short       color,
        void const* opts) {
    if (ERR == mvwchgat(W, y, x, n, attr_map[attrs], color, opts))
        throw "mvwchgat: ERR; y = " + to_string(y) + ", x = " + to_string(x) +
            ", n = " + to_string(n) + ", attrs = " + to_string(attrs.value) +
            ", color = " + to_string(color);
}

void screen::getmaxyx_(int& row, int& col) const {
    getmaxyx(W, row, col);  // macro
}

void screen::getyx_(int& y, int& x) const {
    getyx(W, y, x);         // macro
}

screen::screen(): m_window(initscr()) {
    if (!m_window) throw "initscr: ERR";
    assert(m_window == stdscr);
}

screen::~screen() {
    int r = endwin();
    assert(ERR != r);
}

void screen::clear() {
    if (ERR == wclear(W)) throw "wclear: ERR";
}

void screen::keypad(bool bf) {
    if (ERR == ::keypad(W, bf ? TRUE : FALSE))
        throw "keypad: ERR; bf = " + to_string(bf);
}

void screen::mvprintw(int y, int x, char const* fmt, ...) {
    move_(y, x);
    va_list argp;
    va_start(argp, fmt);
    int r = ::vw_printw(W, fmt, argp);
    va_end(argp);
    if (ERR == r) throw "mvprintw: ERR; fmt = "s + fmt;
}

void screen::refresh() {
    if (ERR == wrefresh(W)) throw "refresh: ERR";
}

void screen::printw(const char* fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    int r = ::vw_printw(W, fmt, argp);
    va_end(argp);
    if (ERR == r) throw "wprintw: ERR; fmt = "s + fmt;
}

#undef W

}
