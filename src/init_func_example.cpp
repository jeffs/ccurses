/** @file init_func_example.cpp Example 2
 * http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/init.html
 */

#include "ccurses.hpp"

#include <iostream> // cerr, endl

class application {

    ccurses::screen m_window;

    void draw();

  public:

    application() {
        ccurses::raw();     // Disable line buffering.
        m_window.keypad();  // Get F1, F2, etc.
        ccurses::noecho();  // Don't echo() while we do getch.
    }

    void main() {
        draw();
        m_window.getch();   // Wait for user input.
    }

};

void application::draw() {
    ccurses::update up(&m_window);
    up.printw("Type any character to see it in bold\n");
    int ch = m_window.getch();      // We called keypad so F1 would get to us.
    if (ch == ccurses::key_f(1)) {
        up.printw("F1 Key pressed");    // Without noecho ugly escape
    } else {                            // characters might have been printed.
        up.printw("The pressed key is ");
        up.attron(ccurses::a_bold);
        up.printw("%c", ch);
        up.attroff(ccurses::a_bold);
    }
}

int main() try {
    application app;
    app.main();
} catch (char const* x) {
    std::cerr << "Error: " << x << std::endl;
} catch (std::string x) {
    std::cerr << "Error: " << x << std::endl;
}
