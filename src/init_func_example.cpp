/** @file init_func_example.cpp Example 2
 * http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/init.html
 */

#include "ccurses.hpp"

#include <iostream> // cerr, endl

class application: ccurses::screen {
    void draw();
  public:

    application() {
        ccurses::raw();     // Disable line buffering.
        keypad();           // Get F1, F2, etc.
        ccurses::noecho();  // Don't echo() while we do getch.
    }

    void main() {
        draw();
        getch();            // Wait for user input.
    }

};

void application::draw() {
    printw("Type any character to see it in bold\n");
    int ch = getch();               // We called keypad so F1 would get to us.
    if (ch == ccurses::key_f(1)) {
        printw("F1 Key pressed");       // Without noecho ugly escape
    } else {                            // characters might have been printed.
        printw("The pressed key is ");
        attron(ccurses::a_bold);
        printw("%c", ch);
        attroff(ccurses::a_bold);
    }
    refresh();
}

int main() try {
    application app;
    app.main();
} catch (char const* x) {
    std::cerr << "Error: " << x << std::endl;
} catch (std::string x) {
    std::cerr << "Error: " << x << std::endl;
}
