#include "game_state.h"

#include "enemy_loader.h"
#include "location_loader.h"

void GameState::Initialize(const std::string& locations_file,
                           const std::string& enemies_file,
                           const std::string& items_file,
                           const std::string& blessings_file) {
  locations_ = LocationLoader::LoadFromFile(locations_file);
  if (!locations_.empty()) {
    current_location_ = &locations_[0];
  } else {
    throw std::runtime_error("No locations loaded");
  }
  enemy_templates_ = EnemyLoader::LoadFromFile(enemies_file);
  item_templates_ = ItemLoader::LoadFromFile(items_file);
  item_templates_.emplace_back("sake_flask", "Фляга Сакэ",
                             "Восстанавливает здоровье", 0, "heal", 30, 30);
  item_templates_.emplace_back("whetstone", "Точильный Камень", "Улучшает меч", 0,
                             "upgrade", 1, 1);
  blessing_templates_ = BlessingLoader::LoadFromFile(blessings_file);
}
