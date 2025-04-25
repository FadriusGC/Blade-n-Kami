#include "GameState.h"
#include "TextView.h"
#include "GameController.h"
#include <iostream>
#include <Windows.h>
#include <sstream>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    try {
        GameState state;
        state.initialize("locations.txt");
        GameController controller(&state);
        Player player;
        /*KuraiBlade blade;*/
        std::string input;
        bool isRunning = true;

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
                    TextView::showMessage("Некорректный ввод!");
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
                    TextView::showMessage("Некорректный ввод!");
                }
                break;
            }

            case MenuState::MOVE_MENU: {
                TextView::showLocation(*state.currentLocation);
                TextView::showAvailableConnections(state);
                std::cout << "[0] Вернуться в меню\nВведите ID локации или 0: ";

                std::cin >> input;
                if (input == "0") {
                    state.currentMenu = MenuState::GAME_MENU;
                    break;
                }

                try {
                    int targetId = std::stoi(input);
                    if (!controller.handleMovement(targetId)) {
                        TextView::showMessage("Неверный выбор локации!");
                    }
                }
                catch (...) {
                    TextView::showMessage("Некорректный ввод!");
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
                    TextView::showMessage("Ошибка ввода!");
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
                    TextView::showMessage("Ошибка ввода!");
                }
                break;
            }
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}