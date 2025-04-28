// TextView.h
#pragma once
#include "GameState.h"
#include <iostream>

class TextView {
public:
    static void clearScreen();
    static void showMainMenu();
    static void showGameMenu();
    static void showLocation(const Location& loc);
    static void showAvailableConnections(const GameState& state);
    static void showMessage(const std::string& msg);
    static void showPlayerMenu(const Player& player);
    static void showKuraiMenu(const KuraiBlade& blade);
    static void showLevelUpMenu(const Player& player);
    static void showEnemyInfo(const Enemy& enemy);
    static void showEnemyList(const std::vector<EnemyData>& enemies);
    static void showEnemyDetails(const Enemy& enemy);
    static void showCombatStats(const Player& player, const Enemy& enemy);
    static void showCombatMenu();
};