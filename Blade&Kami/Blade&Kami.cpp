#include "GameState.h"
#include "TextView.h"
#include "GameController.h"
#include <iostream>

int main() {
    setlocale(LC_ALL, "Russian");
    GameState gameState;
    gameState.initializeLocations();

    GameController controller(&gameState);

    char input;
    do {
        TextView::showLocation(*gameState.currentLocation);
        TextView::showHelp();

        std::cout << "> ";
        std::cin >> input;

        if (input == 'q') break;

        if (!controller.handleInput(input)) {
            std::cout << "Нельзя туда идти!\n";
        }

    } while (true);

    return 0;
}