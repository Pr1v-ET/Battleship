#pragma once

class Menu;

struct MenuItem {
    std::string name;
    bool active;
    enum class Type { ACTION, SUBMENU } type;
    std::function<void()> action;
    Menu* submenu;
    int index;

    MenuItem(std::string n, bool a, Type t, std::function<void()> act, int i)
        : name(std::move(n)), active(a), type(t), action(std::move(act)),
        submenu(nullptr), index(i) {
    }

    MenuItem(std::string n, bool a, Type t, Menu* sub, int i)
        : name(std::move(n)), active(a), type(t), action(nullptr),
        submenu(sub), index(i) {
    }
};
