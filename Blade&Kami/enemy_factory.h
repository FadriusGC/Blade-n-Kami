#ifndef ENEMY_FACTORY_H_
#define ENEMY_FACTORY_H_

#include <stdexcept>

#include "enemy.h"
#include "game_state.h"

class EnemyFactory {
 public:
  static Enemy CreateEnemy(const GameState& state,
                           const std::string& enemy_id) {
    for (const auto& templ : state.enemy_templates_) {
      if (templ.id == enemy_id) {
        return Enemy(templ);
      }
    }
    throw std::runtime_error("Enemy template '" + enemy_id + "' not found");
  }
};

#endif  // ENEMY_FACTORY_H_
