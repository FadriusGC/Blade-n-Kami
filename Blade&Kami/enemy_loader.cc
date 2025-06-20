#include "enemy_loader.h"

#include <fstream>
#include <sstream>

std::vector<EnemyData> EnemyLoader::LoadFromFile(const std::string& filename) {
  std::vector<EnemyData> enemies;
  std::ifstream file(filename);

  if (!file) throw std::runtime_error("Failed to open enemies file");

  EnemyData current;
  std::string line;

  while (getline(file, line)) {
    if (line.empty()) continue;

    if (line[0] == '[') {
      if (!current.id.empty()) {
        enemies.push_back(current);
        current = EnemyData();
      }
      current.id = line.substr(1, line.find(']') - 1);
    } else if (line.find("name=") == 0) {
      current.name = line.substr(5);
    } else if (line.find("level=") == 0) {
      current.level = std::stoi(line.substr(6));
    } else if (line.find("strength=") == 0) {
      current.strength = std::stoi(line.substr(9));
    } else if (line.find("agility=") == 0) {
      current.agility = std::stoi(line.substr(8));
    } else if (line.find("spirit=") == 0) {
      current.spirit = std::stoi(line.substr(7));
    } else if (line.find("evasion=") == 0) {
      current.evasion = std::stod(line.substr(8));
    } else if (line.find("accuracy=") == 0) {
      current.accuracy = std::stod(line.substr(9));
    } else if (line.find("maxHealth=") == 0) {
      current.max_health = std::stoi(line.substr(10));
    } else if (line.find("minDamage=") == 0) {
      current.min_damage = std::stoi(line.substr(10));
    } else if (line.find("maxDamage=") == 0) {
      current.max_damage = std::stoi(line.substr(10));
    } else if (line.find("expReward=") == 0) {
      current.exp_reward = std::stoi(line.substr(10));
    } else if (line.find("goldReward=") == 0) {
      current.gold_reward = std::stoi(line.substr(11));
    }
    // Аналогично для остальных параметров
    else if (line.find("abilities=") == 0) {
      std::stringstream ss(line.substr(10));
      std::string ability;
      while (getline(ss, ability, ',')) {
        current.abilities.push_back(ability);
      }
    }
  }

  if (!current.id.empty()) enemies.push_back(current);
  return enemies;
}
