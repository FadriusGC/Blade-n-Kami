#pragma once
#include "GameState.h"
#include <iostream>

class TextView {
public:
    static void showLocation(const Location& loc) {
        std::cout << "\n=== " << loc.name << " ===\n"
            << loc.description << "\n\n"
            << "Выходы: ";

        for (int id : loc.connectedLocations) {
            std::cout << id << " ";
        }
        std::cout << "\n\n";
    }

    static void showHelp() {
        std::cout << "Команды:\n"
            << "n - на север\n"
            << "s - на юг\n"
            << "q - выход\n";
    }
};
