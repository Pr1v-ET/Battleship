#pragma once

#include <memory>

#include "menu.h"
#include "game.h"

class MenuFactory {
public:
    static std::unique_ptr<Menu> createMainMenu(Game& game);
    static std::unique_ptr<Menu> createGameMenu(Game& game);
    static std::unique_ptr<Menu> createSettingsMenu(Game& game);
    static std::unique_ptr<Menu> createAboutMenu(Game& game);
};

