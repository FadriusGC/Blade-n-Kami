#include "game_state.h"

#include <iostream>
#include <sstream>

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
  /*item_templates_.emplace_back("sake_flask", "Фляга Сакэ",
                                                           "Восстанавливает
     здоровье", 0, "heal", 30, 30);*/
  item_templates_.emplace_back(u8"whetstone", u8"Точильный камень",
                               u8"Улучшает меч", 0, u8"upgrade", 1, 1);
  blessing_templates_ = BlessingLoader::LoadFromFile(blessings_file);
}

void GameState::SaveToFile(const std::string& filename) {
  std::ofstream out(filename);
  if (!out) {
    throw std::runtime_error("Cannot save game");
  }
  out << "[Player]\n";
  out << "level=" << player_.level_ << "\n";
  out << "exp=" << player_.exp_ << "\n";
  out << "gold=" << player_.gold_ << "\n";
  out << "ki=" << player_.ki_ << "\n";
  out << "strength=" << player_.strength_ << "\n";
  out << "agility=" << player_.agility_ << "\n";
  out << "spirit=" << player_.spirit_ << "\n";
  out << "evasion=" << player_.evasion_ << "\n";
  out << "base_health=" << player_.base_health_ << "\n";
  out << "max_health=" << player_.max_health_ << "\n";
  out << "current_health=" << player_.current_health_ << "\n";
  out << "base_reiki=" << player_.base_reiki_ << "\n";
  out << "max_reiki=" << player_.max_reiki_ << "\n";
  out << "current_reiki=" << player_.current_reiki_ << "\n";
  out << "available_points=" << player_.available_points_ << "\n";
  out << "blade_min_damage=" << player_.blade_.min_damage_ << "\n";
  out << "blade_max_damage=" << player_.blade_.max_damage_ << "\n";
  out << "blade_accuracy=" << player_.blade_.accuracy_ << "\n";
  out << "blade_crit_chance=" << player_.blade_.crit_chance_ << "\n";
  out << "blade_spirit_capacity=" << player_.blade_.spirit_capacity_ << "\n";
  out << "[Blessings]\n";
  for (const auto& blessing : player_.blessings_) {
    out << blessing.id << "\n";
  }
  out << "[Inventory]\n";
  out << "whetstones=" << player_inventory_.whetstones_ << "\n";
  out << "sake_charges=" << player_inventory_.sake_charges_ << "\n";
  for (const auto& item : player_inventory_.items_) {
    out << item.id << "\n";
  }
  out << "[Locations]\n";
  for (const auto& loc : locations_) {
    out << loc.id_ << ":" << loc.object_used_ << ":" << loc.enemy_id_ << "\n";
  }
  out << "[Current]\n";
  out << "location_id=" << current_location_->id_ << "\n";
  out << "menu_state=" << static_cast<int>(current_menu_) << "\n";
  out << "[AltarBlessings]\n";
  for (const auto& blessing : current_altar_blessings_) {
    out << blessing.id << "\n";
  }

  out.close();
}

void GameState::LoadFromFile(const std::string& filename) {
  std::ifstream in(filename);
  if (!in) {
    throw std::runtime_error("Cannot load game");
  }

  std::string line;
  std::string section;

  bool blessings_section_started = false;
  bool inventory_section_started = false;
  bool altar_blessings_section_started = false;

  while (std::getline(in, line)) {
    if (line.empty()) continue;

    if (line[0] == '[') {
      section = line;
      blessings_section_started = false;
      inventory_section_started = false;
      altar_blessings_section_started = false;
      continue;
    }

    if (section == "[Player]") {
      std::istringstream iss(line);
      std::string key, value;
      std::getline(iss, key, '=');
      std::getline(iss, value);

      if (key == "level")
        player_.level_ = std::stoi(value);
      else if (key == "exp")
        player_.exp_ = std::stoi(value);
      else if (key == "gold")
        player_.gold_ = std::stoi(value);
      else if (key == "ki")
        player_.ki_ = std::stoi(value);
      else if (key == "strength")
        player_.strength_ = std::stoi(value);
      else if (key == "agility")
        player_.agility_ = std::stoi(value);
      else if (key == "spirit")
        player_.spirit_ = std::stoi(value);
      else if (key == "evasion")
        player_.evasion_ = std::stod(value);
      else if (key == "base_health")
        player_.base_health_ = std::stod(value);
      else if (key == "max_health")
        player_.max_health_ = std::stod(value);
      else if (key == "current_health")
        player_.current_health_ = std::stod(value);
      else if (key == "base_reiki")
        player_.base_reiki_ = std::stod(value);
      else if (key == "max_reiki")
        player_.max_reiki_ = std::stod(value);
      else if (key == "current_reiki")
        player_.current_reiki_ = std::stod(value);
      else if (key == "available_points")
        player_.available_points_ = std::stoi(value);
      else if (key == "blade_min_damage")
        player_.blade_.min_damage_ = std::stoi(value);
      else if (key == "blade_max_damage")
        player_.blade_.max_damage_ = std::stoi(value);
      else if (key == "blade_accuracy")
        player_.blade_.accuracy_ = std::stod(value);
      else if (key == "blade_crit_chance")
        player_.blade_.crit_chance_ = std::stod(value);
      else if (key == "blade_spirit_capacity")
        player_.blade_.spirit_capacity_ = std::stoi(value);

    } else if (section == "[Blessings]") {
      if (!blessings_section_started) {
        player_.blessings_.clear();
        blessings_section_started = true;
      }

      for (const auto& blessing : blessing_templates_) {
        if (blessing.id == line) {
          player_.blessings_.push_back(blessing);
          break;
        }
      }

    } else if (section == "[Inventory]") {
      if (!inventory_section_started) {
        player_inventory_.items_.clear();
        player_inventory_.whetstones_ = 0;
        player_inventory_.sake_charges_ = 0;
        inventory_section_started = true;
      }

      if (line.find('=') != std::string::npos) {
        std::istringstream iss(line);
        std::string key, value;
        std::getline(iss, key, '=');
        std::getline(iss, value);

        if (key == "whetstones")
          player_inventory_.whetstones_ = std::stoi(value);
        else if (key == "sake_charges")
          player_inventory_.sake_charges_ = std::stoi(value);
      } else {
        for (const auto& item_template : item_templates_) {
          if (item_template.id == line) {
            player_inventory_.items_.push_back(item_template);
            break;
          }
        }
      }

    } else if (section == "[Locations]") {
      std::istringstream iss(line);
      std::string token;
      std::vector<std::string> tokens;
      while (std::getline(iss, token, ':')) {
        tokens.push_back(token);
      }

      if (tokens.size() >= 2) {
        int id = std::stoi(tokens[0]);
        bool used = (tokens[1] == "1");
        std::string enemy_id = (tokens.size() >= 3) ? tokens[2] : "";

        for (auto& loc : locations_) {
          if (loc.id_ == id) {
            loc.object_used_ = used;
            loc.enemy_id_ = enemy_id;
            break;
          }
        }
      }

    } else if (section == "[Current]") {
      std::istringstream iss(line);
      std::string key, value;
      std::getline(iss, key, '=');
      std::getline(iss, value);

      if (key == "location_id") {
        for (auto& loc : locations_) {
          if (loc.id_ == std::stoi(value)) {
            current_location_ = &loc;
            break;
          }
        }
      } else if (key == "menu_state") {
        current_menu_ = static_cast<MenuState>(std::stoi(value));
      }

    } else if (section == "[AltarBlessings]") {
      if (!altar_blessings_section_started) {
        current_altar_blessings_.clear();
        altar_blessings_section_started = true;
      }

      for (const auto& blessing : blessing_templates_) {
        if (blessing.id == line) {
          current_altar_blessings_.push_back(blessing);
          break;
        }
      }
    }
  }

  in.close();
}
