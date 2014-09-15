/** @file ccurses.hpp Declares a C++ wrapper around the ncurses library. */

#ifndef INCLUDED_CCURSES
#define INCLUDED_CCURSES

#include <cassert>

namespace ccurses {

struct attribute {

    int value;

    friend attribute operator&(attribute lhs, attribute rhs) {
        return attribute{lhs.value & rhs.value};
    }

    friend attribute operator|(attribute lhs, attribute rhs) {
        return attribute{lhs.value | rhs.value};
    }

    explicit operator bool() const { return value != 0; }

} const
    a_normal     { 1 <<  0 },   // Normal display (no highlight)
    a_standout   { 1 <<  1 },   // Best highlighting mode of the terminal.
    a_underline  { 1 <<  2 },   // Underlining
    a_reverse    { 1 <<  3 },   // Reverse video
    a_blink      { 1 <<  4 },   // Blinking
    a_dim        { 1 <<  5 },   // Half bright
    a_bold       { 1 <<  6 },   // Extra bright or bold
    a_protect    { 1 <<  7 },   // Protected mode
    a_invis      { 1 <<  8 },   // Invisible or blank mode
    a_altcharset { 1 <<  9 },   // Alternate character set
    a_chartext   { 1 << 10 };   // Bit-mask to extract a character

enum class color { black, red, green, yellow, blue, magenta, cyan, white };

extern int const key_left, key_right, key_up, key_down;

struct screen {

    screen();

    void cbreak();

    void init_pair(short pair, color f, color b);

    int key_f(int);

    void noecho();

    void raw();

    void start_color();

    int cols() const;

    int lines() const;
};

class window {
    void* m_window;

    void attroff_(attribute);
    void attron_(attribute);
    void border_(int, int, int, int, int, int, int, int);
    int getch_();
    void getnstr_(char*, int);
    void move_(int, int);
    void mvchgat_(int, int, int, attribute, short, void const*);

    void getmaxyx_(int&, int&) const;
    void getyx_(int&, int&) const;

  public:

    window();

    window(int nlines, int ncols, int begin_x, int begin_y);

    window(window const&) = delete;

    ~window();

    window& operator=(window const&) = delete;

    void attroff(attribute attrs) { attroff_(attrs); }

    void attron(attribute attrs) { attron_(attrs); }

    void border(
            int ls,     // character for left side of window
            int rs,     // character for right side of window
            int ts,     // character for top  side of window
            int bs,     // character for bottom side of window
            int tl,     // character for top left corner of window
            int tr,     // character for top right corner of window
            int bl,     // character for bottom left corner of window
            int br) {   // character for bottom right corner of window
        border_(ls, rs, ts, bs, tl, tr, bl, tr);
    }

    void box(int verch, int horch);

    void clear();

    int getch() { return getch_(); }

    void getnstr(char* str, int n) { getnstr_(str, n); }

    void keypad(bool bf =true);

    void move(int y, int x) { move_(y, x); }

    void mvchgat(
            int         y,
            int         x,
            int         n,
            attribute   attrs,
            short       color,
            void const* opts =nullptr) {
        mvchgat_(y, x, n, attrs, color, opts);
    }

    void mvprintw(int y, int x, char const* fmt, ...);

    void printw(const char* fmt, ...);

    void refresh();

    void getmaxyx(int& row, int& col) const { getmaxyx_(row, col); }

    void getyx(int& y, int& x) const { return getyx_(y, x); }
};

}

#endif
