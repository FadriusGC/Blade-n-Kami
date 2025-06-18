// GameState.h
#pragma once
#include "Location.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include <string>
#include "Inventory.h"
#include "ItemLoader.h"
#include "Blessing.h"
#include "BlessingLoader.h"

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
    LOCATION_MENU,
    ALTAR_MENU,
    BLESSING_MENU,
    BLESSING_COMBAT_MENU,
};

class GameState {
public:
    std::vector<Location> locations;
    std::vector<EnemyData> enemyTemplates;
    std::vector<Item> itemTemplates;  
    std::vector<Blessing> blessingTemplates;
    Location* currentLocation;
    Enemy* currentEnemy = nullptr;
    Enemy* newEnemy = nullptr;
    Inventory playerInventory;
    Player player;
    MenuState currentMenu = MenuState::MAIN_MENU;

    void initialize(const std::string& locationsFile, const std::string& enemiesFile, const std::string& itemsFile, const std::string& blessingsFile);
};