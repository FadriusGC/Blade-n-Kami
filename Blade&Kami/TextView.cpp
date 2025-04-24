// TextView.cpp
#include "TextView.h"
#include <iostream>
#include <cstdlib>

void TextView::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void TextView::showMainMenu() {
    std::cout << "\n=== ГЛАВНОЕ МЕНЮ ===\n"
        << "1. Новая игра\n"
        << "2. Загрузить игру\n"
        << "3. Выход\n"
        << "Выберите вариант: ";
}

void TextView::showGameMenu() {
    std::cout << "\n=== ИГРОВОЕ МЕНЮ ===\n"
        << "1. Передвижение\n"
        << "2. Статы игрока\n"
        << "3. Сохранить игру\n"
        << "4. Главное меню\n"
        << "Выберите действие: ";
}

void TextView::showMessage(const std::string& msg) {
    std::cout << "\n[!] " << msg << "\n";
}
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
    //std::cout << "\nВведите ID локации или 'q' для выхода: ";
}