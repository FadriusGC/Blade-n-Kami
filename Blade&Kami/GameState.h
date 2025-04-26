// GameState.h
#pragma once
#include "Location.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include <string>

enum class MenuState {
    MAIN_MENU,
    GAME_MENU,
    MOVE_MENU,
    PLAYER_MENU,
    COMBAT_MENU,
    KURAI_MENU,
    LVLUP_MENU
};

class GameState {
public:
    std::vector<Location> locations;
    std::vector<EnemyData> enemyTemplates;
    Location* currentLocation;
    Player player; // Добавлен игрок
    /*KuraiBlade blade;*/
    MenuState currentMenu = MenuState::MAIN_MENU;

    void initialize(const std::string& locationsFile, const std::string& enemiesFile);
};