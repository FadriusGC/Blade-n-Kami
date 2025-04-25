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
};