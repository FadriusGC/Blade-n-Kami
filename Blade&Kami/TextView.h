// TextView.h
#pragma once
#include "GameState.h"
#include <iostream>
#include <string>

class TextView {
public:
    static void clearScreen();
    static void showMainMenu();
    static void showGameMenu();
    static void showLocation(const Location& loc);
    static void showAvailableConnections(const GameState& state);
    static void showMessage(const std::string& msg);
    static void showWinMessage(const std::string& msg);
    static void showPlayerMenu(const Player& player);

    static void showKiBar(int kiValue);

    static std::string generateKiBar(int kiValue);

    static void showKuraiMenu(const KuraiBlade& blade);
    static void showLevelUpMenu(const Player& player);
    static void showEnemyInfo(const Enemy& enemy);
    static void showEnemyList(const std::vector<EnemyData>& enemies);
    static void showEnemyDetails(const Enemy& enemy);
    static void showCombatStats(const Player& player, const Enemy& enemy);
    static void showCombatMenu(Player& player, Enemy& enemy);
    static void showInventory(const Inventory& inv);
    static void showInventoryCombat(const Inventory& inv);

    static void showLocationMenu(const Location& loc);
    static void showLocationDetails(const Location& loc);
    static void showChestInteraction(int goldFound);
    static std::string wrapText(const std::string& text, int width = 90);
};