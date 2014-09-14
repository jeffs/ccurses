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

} const a_bold{1}, a_underline{2};

int key_f(int);

int lines();

void noecho();

void raw();

class screen {
    void* m_window;

    void attroff_(attribute);
    void attron_(attribute);
    int getch_();
    void getmaxyx_(int& row, int& col) const;
    void getnstr_(char* str, int n);
    void move_(int y, int x);
  public:

    screen();

    ~screen();

    void attroff(attribute attrs) { attroff_(attrs); }

    void attron(attribute attrs) { attron_(attrs); }

    int getch() { return getch_(); }

    void getnstr(char* str, int n) { getnstr_(str, n); }

    void keypad(bool bf =true);

    void move(int y, int x) { move_(y, x); }

    void mvprintw(int y, int x, char const* fmt, ...);

    void printw(const char* fmt, ...);

    void refresh();

    void getmaxyx(int& row, int& col) const { getmaxyx_(row, col); }
};

}

#endif
