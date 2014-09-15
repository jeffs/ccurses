#include "ccurses.hpp"

#include <ncurses.h>

#include <array>
#include <string>

using namespace std::string_literals;

using std::to_string;

namespace ccurses {

static class system_t {
    bool initialized = false;
  public:

    ~system_t() {
        if (initialized)
            endwin();
    }

    void initialize() {
        if (!initialized) {
            if (!initscr()) throw "initscr: ERR";
            initialized = true;
        }
    }

} system;

static int map_attr(attribute attrs) {
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

int const
    key_left    = KEY_LEFT,
    key_right   = KEY_RIGHT,
    key_up      = KEY_UP,
    key_down    = KEY_DOWN;

// class screen

screen::screen() {
    system.initialize();
}

void screen::cbreak() {
    ::cbreak();
}

void screen::init_pair(short pair, color f, color b) {
    ::init_pair(pair, color_map[int(f)], color_map[int(b)]);
}

int screen::key_f(int i) { return KEY_F(i); }

void screen::noecho() { if (ERR == ::noecho()) throw "noecho: ERR"; }

void screen::raw() { if (ERR == ::raw()) throw "raw: ERR"; }

void screen::start_color() {
    if (ERR == ::start_color()) throw "start_color: ERR";
}

int screen::cols() const { return COLS; }

int screen::lines() const { return LINES; }

// class window

#define W (WINDOW*)m_window

void window::attroff_(attribute attrs) {
    if (ERR == wattroff(W, map_attr(attrs)))
        throw "wattroff: ERR; attrs = " + to_string(attrs.value);
}

void window::attron_(attribute attrs) {
    if (ERR == wattron(W, map_attr(attrs)))
        throw "wattron: ERR; attrs = " + to_string(attrs.value);
}

void window::border_(
        int ls,
        int rs,
        int ts,
        int bs,
        int tl,
        int tr,
        int bl,
        int br) {
    if (ERR == wborder(W, ls, rs, ts, bs, tl, tr, bl, br))
        throw "border: ERR; ls = " + to_string(ls)
            + "rs = " + to_string(rs)
            + "ts = " + to_string(ts)
            + "bs = " + to_string(bs)
            + "tl = " + to_string(tl)
            + "tr = " + to_string(tr)
            + "bl = " + to_string(bl)
            + "br = " + to_string(br);
}

int window::getch_() { // getch is a macro
    int r = wgetch(W);
    if (ERR == r) throw "getch: ERR";
    return r;
}

void window::getnstr_(char* str, int n) {
    int r = wgetnstr(W, str, n);
    if (ERR == r) throw "getnstr: ERR; n = " + to_string(n);
}

void window::move_(int y, int x) {
    if (ERR == wmove(W, y, x))
        throw "move: ERR; y = " + to_string(y) + ", x = " + to_string(x);
}

void window::mvchgat_(
        int         y,
        int         x,
        int         n,
        attribute   attrs,
        short       color,
        void const* opts) {
    if (ERR == mvwchgat(W, y, x, n, map_attr(attrs), color, opts))
        throw "mvwchgat: ERR; y = " + to_string(y) + ", x = " + to_string(x) +
            ", n = " + to_string(n) + ", attrs = " + to_string(attrs.value) +
            ", color = " + to_string(color);
}

void window::getmaxyx_(int& row, int& col) const {
    getmaxyx(W, row, col);  // macro
}

void window::getyx_(int& y, int& x) const {
    getyx(W, y, x);         // macro
}

window::window() {
    system.initialize();
    m_window = stdscr;
}

window::window(int nlines, int ncols, int begin_y, int begin_x) {
    system.initialize();
    m_window = newwin(nlines, ncols, begin_y, begin_x);
    if (!m_window) throw "newwin: ERR; nlines = " + to_string(nlines)
        + ", ncols = " + to_string(ncols)
        + ", begin_x = " + to_string(begin_x)
        + ", begin_y = " + to_string(begin_y);
}

window::~window() {
    if (W != stdscr)
        delwin(W);
}

void window::box(int verch, int horch) {
    if (ERR == ::box(W, chtype(verch), chtype(horch)))
        throw "box: ERR; verch = " + to_string(verch)
            + ", horch = " + to_string(horch);
}

void window::clear() {
    if (ERR == wclear(W)) throw "wclear: ERR";
}

void window::keypad(bool bf) {
    if (ERR == ::keypad(W, bf ? TRUE : FALSE))
        throw "keypad: ERR; bf = " + to_string(bf);
}

void window::mvprintw(int y, int x, char const* fmt, ...) {
    move_(y, x);
    va_list argp;
    va_start(argp, fmt);
    int r = ::vw_printw(W, fmt, argp);
    va_end(argp);
    if (ERR == r) throw "mvprintw: ERR; fmt = "s + fmt;
}

void window::refresh() {
    if (ERR == wrefresh(W)) throw "refresh: ERR";
}

void window::printw(const char* fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    int r = ::vw_printw(W, fmt, argp);
    va_end(argp);
    if (ERR == r) throw "wprintw: ERR; fmt = "s + fmt;
}

#undef W

}
