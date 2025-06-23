#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <string>
#include <vector>

#include "blessing.h"
#include "blessing_loader.h"
#include "enemy.h"
#include "inventory.h"
#include "item_loader.h"
#include "location.h"
#include "player.h"

enum class MenuState {
  kMainMenu,
  kGameMenu,
  kMoveMenu,
  kPlayerMenu,
  kCombatMenu,
  kKuraiMenu,
  kLevelUpMenu,
  kInventoryMenu,
  kInvCombatMenu,
  kLocationMenu,
  kAltarMenu,
  kBlessingMenu,
  kBlessingCombatMenu,
  kEndingMenu,
};

enum class GameEnding { kEvil, kGood, kBloodAndSake, kNone };

class GameState {
 public:
  std::vector<Location> locations_;
  std::vector<EnemyData> enemy_templates_;
  std::vector<Item> item_templates_;
  std::vector<Blessing> blessing_templates_;
  std::vector<Blessing> current_altar_blessings_;
  Location* current_location_;
  Enemy* current_enemy_ = nullptr;
  Enemy* new_enemy_ = nullptr;
  Inventory player_inventory_;
  Player player_;
  MenuState current_menu_ = MenuState::kMainMenu;
  GameEnding ending_ = GameEnding::kNone;
  void Initialize(const std::string& locations_file,
                  const std::string& enemies_file,
                  const std::string& items_file,
                  const std::string& blessings_file);

  void SaveToFile(const std::string& filename);
  void LoadFromFile(const std::string& filename);
};

#endif  // GAMESTATE_H_
