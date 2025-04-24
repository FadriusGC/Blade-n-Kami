#pragma once
#include "GameState.h"
#include <iostream>
#include "TextView.h"
#include "MenuSystem.h"
#include "Player.h"

static void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
};


static void showLocation(const Location& loc) {
    std::cout << "\n=== " << loc.name << " ===\n"
        << loc.description << "\n";
};

static void showAvailableConnections(const GameState& state) {
    std::cout << "\nДоступные переходы:\n";
    for (int connId : state.currentLocation->connections) {
        for (const auto& loc : state.locations) {
            if (loc.id == connId) {
                std::cout << "[" << loc.id << "] " << loc.name << "\n";
                break;
            }
        }
    }
    std::cout << "Введите ID локации или 'b' для возврата: ";
};

static void showPlayerStats(const Player& player) {
    clearScreen();
    std::cout << "=== Характеристики персонажа ===\n"
        << "Уровень: " << player.level << "\n"
        << "Опыт: " << player.exp << "/100\n"
        << "Сила: " << player.strength << "\n"
        << "Ловкость: " << player.agility << "\n"
        << "Дух: " << player.spirit << "\n"
        << "Здоровье: " << player.currentHealth << "/" << player.maxHealth << "\n"
        << "Рэйки: " << player.currentReiki << "/" << player.maxReiki << "\n"
        << "\nНажмите любую клавишу для возврата...";
};