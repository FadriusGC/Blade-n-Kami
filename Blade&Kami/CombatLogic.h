// CombatLogic.h
#pragma once
#include "Player.h"
#include "Enemy.h"
#include <algorithm>

class CombatLogic {
public:
    static void processPlayerAction(Player& player, Enemy& enemy, int action);
    static void processEnemyAction(Player& player, Enemy& enemy);

    static double calculatePurificationChance(Player& player, Enemy& enemy);
    static bool calculateHit(float attackerAccuracy, float targetEvasion);
    static int calculateDamage(int minDmg, int maxDmg);

    static void onEnemyKilled(Player& player, Enemy& enemy);

    static void onEnemyPurified(Player& player, Enemy& enemy);
};