#include <locale.h>
#include <curses.h>

#include "asciiart.h"
#include "game.h"
#include "menu.h"
#include "menufactory.h"

int main() {
    setlocale(LC_ALL, "Russian");
    initscr();
    curs_set(0);
    start_color();
    cbreak();
    noecho();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);

    AsciiArt art;
    attron(COLOR_PAIR(1));
    art.print("Hello BaTTleShip", COLS);
    attroff(COLOR_PAIR(1));
    refresh();

    Game game;
    std::vector<std::unique_ptr<Menu>> menuStack;
    menuStack.push_back(MenuFactory::createMainMenu(game));


    // Создаём окно для меню
    WINDOW* menuWin = newwin(15, 50, 10, 5);
    
    keypad(menuWin, TRUE);
    nodelay(menuWin, TRUE);
    timeout(0);

    // Основной цикл
    int ch;
    bool exit = false;
    do {
        if (!menuStack.empty()) {
            menuStack.back()->render(menuWin);  // Ссылка на верхушку стека!
            wrefresh(menuWin);
        }
        

        ch = wgetch(menuWin);
        if (ch != ERR && !menuStack.empty()) {
            menuStack.back()->handleInput(ch, game, menuStack, exit);  // ВСЁ!
        }
        napms(30);
    } while (!exit);

    keypad(menuWin, FALSE);
    nodelay(menuWin, FALSE);
    timeout(-1);
    delwin(menuWin);
    endwin();
    return 0;
}