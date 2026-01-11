#include "menufactory.h"

std::unique_ptr<Menu> MenuFactory::createMainMenu(Game& game) {
    auto menu = std::make_unique<Menu>(game);
    menu->setTitle("ГЛАВНОЕ МЕНЮ");
    menu->addItem("Игра", true, MenuItem::Type::SUBMENU, nullptr, 0);
    menu->addItem("Настройка", true, MenuItem::Type::SUBMENU, nullptr, 1);
    menu->addItem("Об игре", true, MenuItem::Type::SUBMENU, nullptr, 2);
    menu->addItem("Выход", true, MenuItem::Type::ACTION, []() { }, 3);
    return menu;
}

std::unique_ptr<Menu> MenuFactory::createGameMenu(Game& game) {
    auto menu = std::make_unique<Menu>(game);
    menu->setTitle("НОВАЯ ИГРА");
    menu->addItem("Ручная расстановка кораблей", true, MenuItem::Type::ACTION, []() {}, 0);
    menu->addItem("Автоматическая расстановка кораблей", true, MenuItem::Type::ACTION, []() {}, 1);
    menu->addItem("Назад", true, MenuItem::Type::ACTION, []() {}, 2);
    return menu;
}

std::unique_ptr<Menu> MenuFactory::createSettingsMenu(Game& game) {
    auto menu = std::make_unique<Menu>(game);
    menu->setTitle("НАСТРОЙКИ");
    menu->addItem("Режим игры", true, MenuItem::Type::ACTION, 
        [&game]() { 
            game.setMode(game.getModeIndex() == 0 ? 1 : 0);
        }, 0);
    menu->addItem("Сложность AI", game.getModeIndex() == 1, MenuItem::Type::ACTION,
        [&game]() { 
            if (game.getModeIndex() == 1) {
                game.setDifficulty(game.getDifficultyIndex() < 2 ? game.getDifficultyIndex() + 1 : 0);
            }
        }, 1);
    menu->addItem("Назад", true, MenuItem::Type::ACTION, []() {}, 2);
    return menu;
}

std::unique_ptr<Menu> MenuFactory::createAboutMenu(Game& game) {
    auto menu = std::make_unique<Menu>(game);
    menu->setTitle("ОБ ИГРЕ");
    menu->addItem("История", true, MenuItem::Type::ACTION, []() {}, 0);
    menu->addItem("Правила", true, MenuItem::Type::ACTION, []() {}, 1);
    menu->addItem("Расстановка кораблей", true, MenuItem::Type::ACTION, []() {}, 2);
    menu->addItem("Назад", true, MenuItem::Type::ACTION, []() {}, 3);
    return menu;
}
