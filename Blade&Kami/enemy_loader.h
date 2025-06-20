#ifndef ENEMY_LOADER_H_
#define ENEMY_LOADER_H_

#include <vector>

#include "enemy.h"

class EnemyLoader {
 public:
  static std::vector<EnemyData> LoadFromFile(const std::string& filename);
};

#endif  // ENEMY_LOADER_H_
