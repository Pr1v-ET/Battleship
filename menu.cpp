#include "menu.h"

#define COLOR_GRAY 8

Menu::Menu(Game& g) : game(g), title(""), items(), selectedIndex(0), parent(nullptr) {
}

void Menu::render(WINDOW* win) {
    werase(win);  // очистка
    box(win, 0, 0); // рамка

    // Заголовок
    wattron(win, A_BOLD);
    mvwprintw(win, 1, 2, "%s", title.c_str());
    wattroff(win, A_BOLD);

    init_pair(2, COLOR_GRAY, COLOR_BLACK);

    // Элементы меню
    for (int i = 0; i < items.size(); ++i) {
        auto& item = items[i];
        int y = 4 + i;

        if (i == selectedIndex && item.active) {
            wattron(win, COLOR_PAIR(0) | A_REVERSE);  // выделение
        } else if (i == selectedIndex && !item.active) {
            wattron(win, COLOR_PAIR(2) | A_REVERSE);
        } else if (!(i == selectedIndex) && !item.active) {
            wattron(win, COLOR_PAIR(2));
        }
        if (item.name == "Режим игры") {
            mvwprintw(win, y, 2, "%s %s", item.name.c_str(), game.getMode().c_str());
        } else if (item.name == "Сложность AI") {
            mvwprintw(win, y, 2, "%s %s", item.name.c_str(), game.getDifficulty().c_str());
        } else {
            mvwprintw(win, y, 2, "%s", item.name.c_str());
        }

        wattrset(win, COLOR_PAIR(0));
    }
    wrefresh(win);
}

// Обработка нажатия управляющих кнопок в меню
void Menu::handleInput(int key, Game& game, std::vector<std::unique_ptr<Menu>>& stack,
    bool& exit) {
    int startIndex = selectedIndex;
    switch (key) {
        // Кнопки "стрелка вверх", 'W' и 'w' - одно действие
        case KEY_UP: case 'W': case 'w':
            // Цикл который пропускает "неактивные" пункты
            // Первый круг цикла выполняется в любом случае
            do {
                if (selectedIndex > 0) selectedIndex--;
                else selectedIndex = items.size() - 1;
            // Выход если пункт на который переместились активен
            // или прошли полный круг в "мертвом" меню
            } while (!items[selectedIndex].active && startIndex != selectedIndex);
            break;
        // Кнопки "стрелка вниз", 'S' и 's' - одно дейсвие
        case KEY_DOWN: case 'S': case 's':
            do {
                if (selectedIndex < items.size() - 1) selectedIndex++;
                else selectedIndex = 0;
            } while (!items[selectedIndex].active && startIndex != selectedIndex);
            break;
        // Enter и Пробел - одно действие
        case '\n': case ' ':
            if (!items[selectedIndex].active) return;
            Menu::handleEnter(game, stack, exit);  // Статический? Или передать параметры
            break;

        // Обработка Esc
        // Если мы в подменю - возвращаемся выще
        // Если в главном - меняем флаг для выхода их программы
        case 27:
            if (stack.size() > 1) stack.pop_back();
            else exit = true;
            break;
    }
}

Menu* Menu::getParent() const {
    return parent;
}

void Menu::setTitle(std::string text) {
    title = text;
}

int Menu::getSelectedIndex() {
    return selectedIndex;
}

const std::vector<MenuItem>& Menu::getItems() const {
    return items;
}
std::vector<MenuItem>& Menu::getItemsMutable() {
    return items;
}

void Menu::addItem(std::string name, bool active, MenuItem::Type type,
    std::function<void()> action, int index) {
    items.emplace_back(std::move(name), active, type, std::move(action), index);
}

void Menu::addItem(std::string name, bool active, MenuItem::Type type,
    Menu* submenu, int index) {
    items.emplace_back(std::move(name), active, type, submenu, index);
}

void Menu::handleEnter(Game& game, std::vector<std::unique_ptr<Menu>>& stack, bool& exit) {
    // Выход если ни одного меню не создано и не помещено в очередь
    if (stack.empty()) return;

    // Выделенный пункт из меню на верхушке стека
    int idx = stack.back()->getSelectedIndex();
    auto& item = stack.back()->getItemsMutable()[idx];

    // Возврат в предыдущее меню в стеке
    // Выход если меню верхнее
    if (item.name == "Назад") {
        if (stack.size() > 1) stack.pop_back();
        return;
    }
    // Флаг выхода из главного цикла
    if ((item.name == "Выход")) {
        exit = true;
        return;
    }

    // Если у выбранного пункта есть действия по выбору
    if (item.action) {
        item.action();
        // При изменении "Режима игры" 
        // менять "активность" следующего пункта "Сложность AI"
        if (item.name == "Режим игры")
            stack.back()->getItemsMutable()[++idx].active = game.getModeIndex() == 1;
        return;
    }

    // map Название меню : Функция создания
    static const std::unordered_map<std::string, std::function<std::unique_ptr<Menu>(Game&)>> factories = {
        {"Игра", MenuFactory::createGameMenu},
        {"Настройка", MenuFactory::createSettingsMenu},
        {"Об игре", MenuFactory::createAboutMenu}
    };

    // Поиск меню в списке и запуск соответствующего метода для создания 
    // (если меню найдено в списке)
    auto it = factories.find(item.name);
    if (it != factories.end()) {
        stack.push_back(it->second(game));
    }
}