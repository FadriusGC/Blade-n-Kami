#include "TextView.h"
#include <iostream>



void TextView::showLocation(const Location& loc) {
    std::cout << "\n=== " << loc.name << " ===\n"
        << loc.description << "\n\n";
}

void TextView::showAvailableConnections(const GameState& state) {
    std::cout << "Доступные переходы:\n";
    for (int connId : state.currentLocation->connections) {
        for (const auto& loc : state.locations) {
            if (loc.id == connId) {
                std::cout << "[" << loc.id << "] " << loc.name << "\n";
                break;
            }
        }
    }
    std::cout << "\nВведите ID локации или 'q' для выхода: ";
}