#include "location_loader.h"

#include <sstream>

std::vector<Location> LocationLoader::LoadFromFile(
    const std::string& filename) {
  std::vector<Location> locations;
  std::ifstream file(filename);

  if (!file) {
    throw std::runtime_error("Failed to open locations file");
  }

  int current_id = -1;
  std::string line;
  std::string name, desc, detailed_desc;
  std::vector<int> conn;
  std::string enemy_id, object_id;

  while (getline(file, line)) {
    if (line.empty()) continue;

    if (line[0] == '[') {
      if (current_id != -1) {
        locations.emplace_back(current_id, name, desc, detailed_desc, conn,
                               enemy_id, object_id);
        conn.clear();
        detailed_desc.clear();
        object_id.clear();
        enemy_id.clear();
      }
      current_id = std::stoi(line.substr(1, line.find(']') - 1));
    } else if (line.find("name=") == 0) {
      name = line.substr(5);
    } else if (line.find("description=") == 0) {
      desc = line.substr(12);
    } else if (line.find("detailedDescription=") == 0) {
      detailed_desc = line.substr(20);
    } else if (line.find("connections=") == 0) {
      std::stringstream ss(line.substr(12));
      std::string token;
      while (getline(ss, token, ',')) {
        conn.push_back(std::stoi(token));
      }
    } else if (line.find("enemyID=") == 0) {
      enemy_id = line.substr(8);
    } else if (line.find("objectID=") == 0) {
      object_id = line.substr(9);
    }
  }

  if (current_id != -1) {
    locations.emplace_back(current_id, name, desc, detailed_desc, conn,
                           enemy_id, object_id);
  }

  return locations;
}
