/** @file simple_attr.cpp Example 5
 * http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/attrib.html
 *
 * pager functionality by Joseph Spainhour <spainhou@bellsouth.net>
 */

#include "ccurses.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <iostream>

using namespace std::string_literals;

int main(int argc, char *argv[]) try {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <a c file name>\n";
        exit(1);
    }

    FILE* fp = fopen(argv[1], "r");
    if (!fp)
        throw "Cannot open input file: "s + std::strerror(errno);

    ccurses::screen w;

    int row, col;
    w.getmaxyx(row, col);

    for (int ch = fgetc(fp), prev = EOF; ch != EOF; ch = fgetc(fp)) {
        int y, x;
        w.getyx(y, x);
        if (y == row - 1) {
            w.printw("<-Press Any Key->");
            w.getch();
            w.clear();
            w.move(0, 0);
        }
        if (prev == '/' && ch == '*') {
            w.attron(ccurses::a_bold);
            w.getyx(y, x);
            w.move(y, x - 1);
            w.printw("%c%c", '/', ch);
        } else {
            w.printw("%c", ch);
        }
        w.refresh();
        if (prev == '*' && ch == '/')
            w.attroff(ccurses::a_bold);
        prev = ch;
    }
    fclose(fp);
} catch (char const* x) {
    std::cerr << "Error: " << x << std::endl;
    return 1;
} catch (std::string x) {
    std::cerr << "Error: " << x << std::endl;
    return 1;
}
