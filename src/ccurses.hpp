/** @file ccurses.hpp Declares a C++ wrapper around the ncurses library. */

#ifndef INCLUDED_CCURSES
#define INCLUDED_CCURSES

namespace ccurses {

class screen {
    void* m_window;
  public:

    screen();

    ~screen();
};

class update {
    void getch_();
public:

    explicit update(screen* s) { }

    ~update();

    void getch() { getch_(); }

    void printw(const char* fmt, ...);

    void refresh();
};

}


#endif
