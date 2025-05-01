#include "GameState.h"
#include "TextView.h"
#include "GameController.h"
#include <iostream>
#include <Windows.h>
#include <sstream>
#include "EnemyFactory.h"
#include "Localisation.h"
#include "CombatSystem.h"
#include "AbilityHandler.h"
#include "Inventory.h"
#include "ItemFactory.h"

int main() {
    /*SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");*/
    //SetConsoleOutputCP(CP_UTF8);  // Устанавливаем UTF-8 для вывода
    //SetConsoleCP(CP_UTF8);        // Устанавливаем UTF-8 для ввода
    localise();
    try {
        GameState state;
        state.initialize("locations.txt", "enemies.txt", "items.txt");
        AbilityHandler::initAbilities();
        GameController controller(&state);
        Player player;
        /*KuraiBlade blade;*/
        std::string input;
        bool isRunning = true;
        //Enemy* currentEnemy = nullptr;
        TextView::showMessage(u8"Тест загрузки врагов:");
        TextView::showEnemyList(state.enemyTemplates);

        state.playerInventory.addItem("health_potion", state);
        state.playerInventory.addItem("bomb", state);
        state.playerInventory.addItem("health_potion", state);

        // Создайте тестового врага
        Enemy testEnemy = EnemyFactory::createEnemy(state, "wolf");
        TextView::showEnemyDetails(testEnemy);
        Enemy testEnemy2 = EnemyFactory::createEnemy(state, "goblin");
        TextView::showEnemyDetails(testEnemy2);

        while (isRunning) {
            std::cin.ignore();
            TextView::clearScreen();
            switch (state.currentMenu) {
            case MenuState::MAIN_MENU: {
                TextView::showMainMenu();
                std::cin >> input;
                try {
                    int choice = std::stoi(input);
                    isRunning = controller.handleMainMenu(choice);
                }
                catch (...) {
                    TextView::showMessage(u8"Некорректный ввод!");
                }
                break;
            }

            case MenuState::GAME_MENU: {
                TextView::showGameMenu();
                std::cin >> input;
                try {
                    int choice = std::stoi(input);
                    controller.handleGameMenu(choice);
                }
                catch (...) {
                    TextView::showMessage(u8"Некорректный ввод!");
                }
                break;
            }

            case MenuState::MOVE_MENU: {
                TextView::showLocation(*state.currentLocation);
                TextView::showAvailableConnections(state);
                std::cout << u8"[0] Вернуться в меню\nВведите ID локации или 0: ";

                std::cin >> input;
                if (input == "0") {
                    state.currentMenu = MenuState::GAME_MENU;
                    break;
                }

                try {
                    int targetId = std::stoi(input);
                    if (!controller.handleMovement(targetId)) {
                        TextView::showMessage(u8"Неверный выбор локации!");
                    }
                }
                catch (...) {
                    TextView::showMessage(u8"Некорректный ввод!");
                }
                break;
            }

            case MenuState::PLAYER_MENU: {
                TextView::showPlayerMenu(state.player);
                std::cin >> input;
                try {
                    int choice = std::stoi(input);
                    controller.handlePlayerMenu(choice);
                }
                catch (...) {
                    TextView::showMessage(u8"Ошибка ввода!");
                }
                break;
            }

            case MenuState::KURAI_MENU: {
                TextView::showKuraiMenu(state.player.blade);
                std::cin >> input;
                try {
                    int choice = std::stoi(input);
                    controller.handleKuraiMenu(choice);
                }
                catch (...) {
                    TextView::showMessage(u8"Ошибка ввода!");
                }
                break;
            }
            case MenuState::COMBAT_MENU: {
                // Инициализация боя при входе
                if (!state.currentEnemy && state.currentLocation->enemyID != "") {
                    state.currentEnemy = new Enemy(EnemyFactory::createEnemy(state, state.currentLocation->enemyID)); // <--- во тута ахуительная утечка памяти, потому что я не делитаю указатель, а ставлю его нуллптр. Не ебу как фикисть, осталю так
                } // <- чисто в теории можно сделать еще один указатели типо темп_енеми который как раз будет присваиваться куррент энеми и уже темп энеми мы будем удалять полностью а куррент просто очищать

                // Отображение интерфейса
                TextView::showCombatStats(state.player, *state.currentEnemy);
                TextView::showCombatMenu();

                // Ввод игрока
                //std::string input;
                std::cin >> input;

                try {
                    int choice = std::stoi(input);
                    auto result = controller.handleCombatMenu(choice, *state.currentEnemy);

                    // Обработка результатов
                    switch (result) {
                    case CombatSystem::PLAYER_WIN:
                        TextView::showMessage(u8"Победа! Опыт +"
                            + std::to_string(state.currentEnemy->data.expReward));

                        state.player.gainExp(state.currentEnemy->data.expReward);
                        //state.player.exp += currentEnemy->data.expReward;
                        state.currentEnemy = nullptr;
                        state.currentLocation->enemyID = "";
                        std::cin.ignore();
                        state.currentMenu = MenuState::GAME_MENU;
                        break;

                    case CombatSystem::ENEMY_WIN:
                        TextView::showMessage(u8"Игрок погиб, игра окончена :(");
                        std::cin.ignore();
                        exit(0);

                    case CombatSystem::FLEE:
                        state.currentMenu = MenuState::GAME_MENU;
                        state.currentEnemy = nullptr;
                        break;
                    }
                }
                catch (...) {
                    TextView::showMessage(u8"Ошибка ввода!");
                }
                break;
            }
            case MenuState::LEVEL_UP_MENU: {
                TextView::showLevelUpMenu(state.player);
                //std::string input;
                std::cin >> input;

                try {
                    int choice = std::stoi(input);
                    controller.handleLevelUpMenu(choice);
                }
                catch (...) {
                    TextView::showMessage(u8"Некорректный ввод!");
                }
                break;
            }
            case MenuState::INVENTORY_MENU: {
                TextView::showInventory(state.playerInventory);
                std::cin >> input;
                try {
                    int choice = std::stoi(input);
                    controller.handleInventoryMenu(choice);
                }
                catch (...) {
                    TextView::showMessage(u8"Некорректный ввод!");
                }
                break;
            }
            case MenuState::INV_COMBAT_MENU: {
                TextView::showInventoryCombat(state.playerInventory);
                std::cin >> input;
                int choice = std::stoi(input);
                controller.handleInventoryCombatMenu(choice);
                break;
            }
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << u8"Ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
