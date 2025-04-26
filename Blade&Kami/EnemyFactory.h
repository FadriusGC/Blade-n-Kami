// EnemyFactory.h
#pragma once
#include "Enemy.h"
#include "GameState.h"
#include <stdexcept>

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