/** @file ccurses.hpp Declares a C++ wrapper around the ncurses library. */

#ifndef INCLUDED_CCURSES
#define INCLUDED_CCURSES

namespace ccurses {

enum class a { bold };

namespace detail { int getch_(); }
inline int getch() { return detail::getch_(); }

int key_f(int);

void noecho();

void raw();

class screen {
    void* m_window;

  public:

    screen();

    ~screen();

    void keypad(bool bf =true);

    void wprintw(const char* fmt, ...);
};

class update {
    screen* m_window;

    void attroff_(a);
    void attron_(a);
  public:

    explicit update(screen* window): m_window(window) { }

    ~update();

    void attroff(a attribute) { attroff_(attribute); }

    void attron(a attribute) { attron_(attribute); }

    template <class... T>
    void printw(const char* fmt, T... xs) { m_window->wprintw(fmt, xs...); }

    void refresh();
};

}

#endif
