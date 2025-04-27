#include "GameState.h"
#include "TextView.h"
#include "GameController.h"
#include <iostream>
#include <Windows.h>
#include <sstream>
#include "EnemyFactory.h"
#include "Localisation.h"
#include "CombatSystem.h"

int main() {
    /*SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");*/
    //SetConsoleOutputCP(CP_UTF8);  // Устанавливаем UTF-8 для вывода
    //SetConsoleCP(CP_UTF8);        // Устанавливаем UTF-8 для ввода
    localise();
    try {
        GameState state;
        state.initialize("locations.txt", "enemies.txt");
        GameController controller(&state);
        Player player;
        /*KuraiBlade blade;*/
        std::string input;
        bool isRunning = true;
        Enemy* currentEnemy = nullptr;
        TextView::showMessage(u8"Тест загрузки врагов:");
        TextView::showEnemyList(state.enemyTemplates);

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
                if (!currentEnemy && state.currentLocation->enemyID != "") {
                    currentEnemy = new Enemy(EnemyFactory::createEnemy(state, state.currentLocation->enemyID));
                }

                // Отображение интерфейса
                TextView::showCombatStats(state.player, *currentEnemy);
                TextView::showCombatMenu();

                // Ввод игрока
                std::string input;
                std::cout << u8"> ";
                std::cin >> input;

                try {
                    int choice = std::stoi(input);
                    auto result = controller.handleCombatMenu(choice, *currentEnemy);

                    // Обработка результатов
                    switch (result) {
                    case CombatSystem::PLAYER_WIN:
                        TextView::showMessage(u8"Победа! Опыт +"
                            + std::to_string(currentEnemy->data.expReward));
                        state.player.exp += currentEnemy->data.expReward;
                        currentEnemy = nullptr;
                        state.currentLocation->enemyID = "";
                        std::cin.ignore();
                        state.currentMenu = MenuState::GAME_MENU;
                        break;

                    case CombatSystem::ENEMY_WIN:
                        TextView::showMessage(u8"Игрок погиб");
                        std::cin.ignore();
                        exit(0);

                    case CombatSystem::FLEE:
                        state.currentMenu = MenuState::GAME_MENU;
                        currentEnemy = nullptr;
                        break;
                    }
                }
                catch (...) {
                    TextView::showMessage(u8"Ошибка ввода!");
                }
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
