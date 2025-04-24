#include "GameState.h"
#include "TextView.h"
#include "GameController.h"
#include <iostream>
#include <Windows.h>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    try {
        GameState state;
        state.initialize("locations.txt");

        GameController controller(&state);
        std::string input;

        while (true) {
            TextView::showLocation(*state.currentLocation);
            TextView::showAvailableConnections(state);

            std::cin >> input;
            if (input == "q") break;

            try {
                int targetId = std::stoi(input);
                if (!controller.handleInput(targetId)) {
                    std::cout << "Неверный выбор!\n";
                }
            }
            catch (...) {
                std::cout << "Введите число или 'q'!\n";
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}