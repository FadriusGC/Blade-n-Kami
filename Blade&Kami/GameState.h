// GameState.h
#pragma once
#include <string>
#include <vector>

#include "Blessing.h"
#include "BlessingLoader.h"
#include "Enemy.h"
#include "Inventory.h"
#include "ItemLoader.h"
#include "Location.h"
#include "Player.h"

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
  std::vector<Blessing> currentAltarBlessings;
  Location* currentLocation;
  Enemy* currentEnemy = nullptr;
  Enemy* newEnemy = nullptr;
  Inventory playerInventory;
  Player player;
  MenuState currentMenu = MenuState::MAIN_MENU;

  void initialize(const std::string& locationsFile,
                  const std::string& enemiesFile, const std::string& itemsFile,
                  const std::string& blessingsFile);
};
