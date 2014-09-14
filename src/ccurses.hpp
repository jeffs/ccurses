/** @file ccurses.hpp Declares a C++ wrapper around the ncurses library. */

#ifndef INCLUDED_CCURSES
#define INCLUDED_CCURSES

#include <cassert>

namespace ccurses {

enum class a { bold };

int key_f(int);

void noecho();

void raw();

class screen {
    void* m_window;

    void attroff_(a);
    void attron_(a);
    int getch_();
  public:

    screen();

    ~screen();

    void attroff(a attr) { attroff_(attr); }

    void attron(a attr) { attron_(attr); }

    int getch() { return getch_(); }

    void keypad(bool bf =true);

    void printw(const char* fmt, ...);

    void refresh();
};

class update {
    screen* m_window;
  public:

    explicit update(screen* window): m_window(window) { }

    ~update();

    void attroff(a attr) { m_window->attroff(attr); }

    void attron(a attr) { m_window->attron(attr); }

    template <class... T>
    void printw(const char* fmt, T... xs) { m_window->printw(fmt, xs...); }

    void refresh() { m_window->refresh(); }
};

}

#endif
