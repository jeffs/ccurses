/** @file ccurses.hpp Declares a C++ wrapper around the ncurses library. */

#ifndef INCLUDED_CCURSES
#define INCLUDED_CCURSES

#include <cassert>

namespace ccurses {

struct a {
    int value;

    friend a operator&(a lhs, a rhs) { return a{lhs.value & rhs.value}; }
    friend a operator|(a lhs, a rhs) { return a{lhs.value | rhs.value}; }

    explicit operator bool() const { return value != 0; }

} const a_bold{1}, a_underline{2};


int key_f(int);

void noecho();

void raw();

class screen {
    void* m_window;

    void attroff_(a);
    void attron_(a);
    int getch_();
    void getmaxyx_(int& row, int& col) const;
    void move_(int y, int x);
  public:

    screen();

    ~screen();

    void attroff(a attrs) { attroff_(attrs); }

    void attron(a attrs) { attron_(attrs); }

    int getch() { return getch_(); }

    void keypad(bool bf =true);

    void move(int y, int x) { move_(y, x); }

    void mvprintw(int y, int x, char const* fmt, ...);

    void printw(const char* fmt, ...);

    void refresh();

    void getmaxyx(int& row, int& col) const { getmaxyx_(row, col); }
};

}

#endif
