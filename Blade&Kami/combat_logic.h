#ifndef COMBAT_LOGIC_H_
#define COMBAT_LOGIC_H_

#include <algorithm>

#include "enemy.h"
#include "player.h"

class CombatLogic {
 public:
  static void ProcessPlayerAction(Player& player, Enemy& enemy, int action);
  static void ProcessEnemyAction(Player& player, Enemy& enemy);

  static double CalculatePurificationChance(Player& player, Enemy& enemy);
  static bool CalculateHit(float attacker_accuracy, float target_evasion);
  static int CalculateDamage(int min_dmg, int max_dmg);

  static void OnEnemyKilled(Player& player, Enemy& enemy);

  static void OnEnemyPurified(Player& player, Enemy& enemy);

  static void ProcessEndOfTurnEffects(Player& player);
};

#endif  // COMBAT_LOGIC_H_
