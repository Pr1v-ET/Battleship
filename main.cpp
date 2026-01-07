#include "asciiart.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);

    AsciiArt art;
    attron(COLOR_PAIR(1));
    art.print("Hello BaTTleShip", COLS);
    attroff(COLOR_PAIR(1));

    refresh();
    getch();
    endwin();
    return 0;
}