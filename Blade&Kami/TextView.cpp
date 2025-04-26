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

void TextView::showPlayerMenu(const Player& player) {
    std::cout << "\n=== ХАРАКТЕРИСТИКИ ИГРОКА ===\n"
        << "Уровень: " << player.level << "\n"
        << "Здоровье: " << player.currentHealth << "/" << player.maxHealth << "\n"
        << "Рейки: " << player.currentReiki << "/" << player.maxReiki << "\n"
        << "Сила: " << player.strength << "\n"
        << "Ловкость: " << player.agility << "\n"
        << "Дух: " << player.spirit << "\n"
        << "[1] Улучшить силу\n[2] Улучшить дух\n[3] Показать статы Курай\n[0] Назад\nВыбор: ";
}

void TextView::showKuraiMenu(const KuraiBlade& blade) {
    std::cout << "\n=== МЕЧ КУРАЙ ===\n"
        << "Урон: " << blade.minDamage << "-" << blade.maxDamage << "\n"
        << "Точность: " << blade.accuracy << "\n"
        << "Крит: " << blade.critChance << "\n"
        << "[1] Улучшить урон\n[2] Улучшить точность\n[0] Назад\nВыбор: ";
}

void TextView::showEnemyInfo(const Enemy& enemy) {
    std::cout << "\n=== " << enemy.data.name << " ===\n"
        << "Здоровье: " << enemy.data.currentHealth << "/" << enemy.data.maxHealth << "\n"
        << "Урон: " << enemy.data.minDamage << "-" << enemy.data.maxDamage << "\n"
        << "Уровень: " << enemy.data.level << "\n";
}

void TextView::showEnemyList(const std::vector<EnemyData>& enemies) {
    std::cout << "\n=== ЗАГРУЖЕННЫЕ ВРАГИ ===";
    for (const auto& e : enemies) {
        std::cout << "\n[" << e.id << "] " << e.name
            << " (Уровень: " << e.level << ")";
    }
    std::cout << "\n";
}

void TextView::showEnemyDetails(const Enemy& enemy) {
    const auto& d = enemy.data;
    std::cout << "\n=== " << d.name << " ===\n"
        << "ID: " << d.id << "\n"
        << "Уровень: " << d.level << "\n"
        << "Здоровье: " << d.currentHealth << "/" << d.maxHealth << "\n"
        << "Урон: " << d.minDamage << "-" << d.maxDamage << "\n"
        << "Точность: " << d.accuracy * 100 << "%\n"
        << "Дух: " << d.spirit << "\n"
        << "Сила: " << d.strength << "\n"
        << "Способности: ";
    for (const auto& a : d.abilities) {
        std::cout << a << " ";
    }
    std::cout << "\n";
}