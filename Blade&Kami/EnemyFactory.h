// EnemyFactory.h
#pragma once
#include <stdexcept>

#include "Enemy.h"
#include "GameState.h"

class EnemyFactory {
 public:
  static Enemy createEnemy(const GameState& state, const std::string& enemyId) {
    for (const auto& templ : state.enemyTemplates) {
      if (templ.id == enemyId) {
        return Enemy(templ);
      }
    }
    throw std::runtime_error("Enemy template '" + enemyId + "' not found");
  }
};
