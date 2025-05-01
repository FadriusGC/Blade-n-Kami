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
    std::cout << u8"\n=== ГЛАВНОЕ МЕНЮ ===\n"
        << u8"[1] Новая игра\n"
        << u8"[2] Загрузить игру\n"
        << u8"[3] Выход\n"
        << u8"====================\n"
        << u8"Выберите вариант: ";
}

void TextView::showGameMenu() {
    std::cout << u8"\n=== ИГРОВОЕ МЕНЮ ===\n"
        << u8"[1] Передвижение\n"
        << u8"[2] Статы игрока\n"
        << u8"[3] Сохранить игру\n"
        << u8"[4] Главное меню\n"
        << u8"====================\n"
        << u8"Выберите действие: ";
}

void TextView::showMessage(const std::string& msg) {
    std::cout << u8"\n[!] " << msg << "\n";
}
void TextView::showLocation(const Location& loc) {
    std::cout << u8"\n=== " << loc.name << " ===\n"
        << loc.description << "\n\n";
}

void TextView::showAvailableConnections(const GameState& state) {
    std::cout << u8"Доступные переходы:\n";
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
    std::cout << u8"\n=== ХАРАКТЕРИСТИКИ ИГРОКА ===\n"
        << u8"🌟 Уровень: " << player.level << u8" Опыт: "<< player.exp << u8"/" << player.requiredExp << "\n"
        << u8"❤️ Здоровье: " << player.currentHealth << "/" << player.maxHealth << "\n"
        << u8"🌀 Рейки: " << player.currentReiki << "/" << player.maxReiki << "\n"
        << u8"💪 Сила: " << player.strength << "\n"
        << u8"🏹 Ловкость: " << player.agility << "\n"
        << u8"🧿 Дух: " << player.spirit << "\n"
        << "=============================" << "\n"
        << u8"[1] Прокачка характеристик\n[2] Показать статы Курай\n[3] Инвентарь\n[0] Назад\n=============================\nВыбор: ";
}

void TextView::showKuraiMenu(const KuraiBlade& blade) {
    std::cout << u8"\n=== МЕЧ КУРАЙ ===\n"
        << u8"Урон: " << blade.minDamage << "-" << blade.maxDamage << "\n"
        << u8"Точность: " << blade.accuracy << "\n"
        << u8"Крит: " << blade.critChance << "\n"
        << u8"=================" << "\n"
        << u8"[1] Улучшить урон\n[2] Улучшить точность\n[0] Назад\n" << "=================\n" << u8"Выбор: ";
}

void TextView::showEnemyInfo(const Enemy& enemy) {
    std::cout << "\n=== " << enemy.data.name << " ===\n"
        << u8"Здоровье: " << enemy.data.currentHealth << "/" << enemy.data.maxHealth << "\n"
        << u8"Урон: " << enemy.data.minDamage << "-" << enemy.data.maxDamage << "\n"
        << u8"Уровень: " << enemy.data.level << "\n";
}

void TextView::showEnemyList(const std::vector<EnemyData>& enemies) {
    std::cout << u8"\n=== ЗАГРУЖЕННЫЕ ВРАГИ ===";
    for (const auto& e : enemies) {
        std::cout << "\n[" << e.id << "] " << e.name
            << u8" (Уровень: " << e.level << ")";
    }
    std::cout << "\n";
}

void TextView::showEnemyDetails(const Enemy& enemy) {
    const auto& d = enemy.data;
    std::cout << "\n=== " << d.name << " ===\n"
        << u8"ID: " << d.id << "\n"
        << u8"Уровень: " << d.level << "\n"
        << u8"Здоровье: " << d.currentHealth << "/" << d.maxHealth << "\n"
        << u8"Урон: " << d.minDamage << "-" << d.maxDamage << "\n"
        << u8"Точность: " << d.accuracy * 100 << "%\n"
        << u8"Дух: " << d.spirit << "\n"
        << u8"Сила: " << d.strength << "\n"
        << u8"Способности: ";
    for (const auto& a : d.abilities) {
        std::cout << a << " ";
    }
    std::cout << "\n";
}

void TextView::showCombatStats(const Player& player, const Enemy& enemy) {
    std::cout << u8"\n=== БОЙ ===\n"
        << u8"Игрок: " << player.currentHealth << u8"/" << player.maxHealth << u8" HP\n"
        << u8"Урон: " << player.blade.minDamage << u8"-" << player.blade.maxDamage << "\n"
        << u8"Точность: " << (player.blade.accuracy * 100) << u8"%\n"
        << u8"----vs.----\n" << u8"Враг (" << enemy.data.name << u8"): "
        << enemy.data.currentHealth << u8"/" << enemy.data.maxHealth << u8" HP\n"
        << u8"Урон врага: " << enemy.data.minDamage << u8"-" << enemy.data.maxDamage << u8"\n"
        << u8"Точность врага: " << (enemy.data.accuracy * 100) << u8"%\n";
}

void TextView::showCombatMenu() {
    std::cout << u8"===========\n[1] Атака\n[5] Бежать\n===========\nВыбор: ";
}

void TextView::showLevelUpMenu(const Player& player) {
    std::cout << u8"\n=== ПРОКАЧКА ХАРАКТЕРИСТИК ===\n"
        << u8"Доступно очков: " << player.availablePoints << "\n" << u8"==============================" << "\n"
        << u8"[1] Сила: " << player.strength << "\n"
        << u8"[2] Ловкость: " << player.agility << "\n"
        << u8"[3] Дух: " << player.spirit << "\n"
        << u8"[0] Выход\n"
        << u8"==============================" << "\n"
        << u8"Какую характеристику улучшить: ";
}

void TextView::showInventory(const Inventory& inv) {
    std::cout << u8"\n=== ИНВЕНТАРЬ ===\n";
    std::cout << u8"Фляга Сакэ: " << inv.sakeCharges << u8" зарядов\n";

    for (const auto& item : inv.items) {
        std::cout << u8"- " << item.name << ": " << item.desc << u8"\n";
    }
    std::cout << u8"\n[0] Выход";
}