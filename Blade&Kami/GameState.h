﻿// GameState.h
#pragma once
#include "Location.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include <string>
#include "Inventory.h"
#include "ItemLoader.h"

enum class MenuState {
    MAIN_MENU,
    GAME_MENU,
    MOVE_MENU,
    PLAYER_MENU,
    COMBAT_MENU,
    KURAI_MENU,
    LEVEL_UP_MENU,
    INVENTORY_MENU,
    INV_COMBAT_MENU,
};

class GameState {
public:
    std::vector<Location> locations;
    std::vector<EnemyData> enemyTemplates;
    std::vector<Item> itemTemplates;  // Библиотека всех предметов
    Location* currentLocation;
    Enemy* currentEnemy = nullptr;
    Inventory playerInventory;
    Player player;
    MenuState currentMenu = MenuState::MAIN_MENU;

    void initialize(const std::string& locationsFile, const std::string& enemiesFile, const std::string& itemsFile);
};