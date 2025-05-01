// CombatSystem.h
#pragma once
#include "Player.h"
#include "Enemy.h"
#include "GameState.h"

class CombatSystem {
public:
    enum CombatResult { IN_PROGRESS, PLAYER_WIN, ENEMY_WIN, FLEE };

    static CombatResult updateCombat(Player& player, Enemy& enemy, int playerAction, GameState& state);
};