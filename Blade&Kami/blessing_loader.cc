#include "blessing_loader.h"

#include <stdexcept>

std::vector<Blessing> BlessingLoader::LoadFromFile(
    const std::string& filename) {
  std::vector<Blessing> blessings;
  std::ifstream file(filename);

  if (!file) {
    throw std::runtime_error("Failed to open blessings file");
  }

  std::string line;
  std::string current_id;
  std::string name, desc, ability, kami, kami_type;
  BlessingType type = BlessingType::kPassive;
  int base_power = 0, reiki_cost = 0;

  while (getline(file, line)) {
    if (line.empty()) continue;

    if (line[0] == '[') {
      // Сохраняем предыдущее благословение
      if (!current_id.empty()) {
        blessings.emplace_back(current_id, name, desc, kami, kami_type, type,
                               ability, base_power, reiki_cost);
      }

      // Начинаем новое благословение
      current_id = line.substr(1, line.find(']') - 1);
      name.clear();
      desc.clear();
      kami.clear();
      kami_type.clear();
      ability.clear();
      type = BlessingType::kPassive;
      base_power = 0;
      reiki_cost = 0;
    } else if (line.find("name=") == 0) {
      name = line.substr(5);
    } else if (line.find("description=") == 0) {
      desc = line.substr(12);
    } else if (line.find("kami=") == 0) {
      kami = line.substr(5);
    } else if (line.find("kamiType=") == 0) {
      kami_type = line.substr(9);
    } else if (line.find("type=") == 0) {
      std::string typeStr = line.substr(5);
      type = (typeStr == "active") ? BlessingType::kActive
                                   : BlessingType::kPassive;
    } else if (line.find("ability=") == 0) {
      ability = line.substr(8);
    } else if (line.find("basePower=") == 0) {
      base_power = std::stoi(line.substr(10));
    } else if (line.find("reikiCost=") == 0) {
      reiki_cost = std::stoi(line.substr(10));
    }
  }

  // Сохраняем последнее благословение
  if (!current_id.empty()) {
    blessings.emplace_back(current_id, name, desc, kami, kami_type, type,
                           ability, base_power, reiki_cost);
  }

  return blessings;
}
