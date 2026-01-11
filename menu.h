#pragma once

#include <vector>
#include <curses.h>
#include <functional>
#include <memory>

#include "game.h"
#include "menuitem.h"
#include "menufactory.h"

class Menu {
private:
    Game& game;
    std::string title;
    std::vector<MenuItem> items;
    int selectedIndex;
    Menu* parent;
public:
    Menu(Game& game);
    void render(WINDOW* win);
    void addItem(std::string name, bool active, MenuItem::Type type,
        std::function<void()> action, int index);
    void addItem(std::string name, bool active, MenuItem::Type type,
        Menu* submenu, int index);
    void handleInput(int key, Game& game, std::vector<std::unique_ptr<Menu>>& stack, 
        bool& exit);
    Menu* getParent() const;

    void setTitle(std::string text);
    int getSelectedIndex();
    const std::vector<MenuItem>& getItems() const;
    std::vector<MenuItem>& getItemsMutable();
    static void handleEnter(Game& game, std::vector<std::unique_ptr<Menu>>& stack, bool& exit);
    void updateActivity();
};