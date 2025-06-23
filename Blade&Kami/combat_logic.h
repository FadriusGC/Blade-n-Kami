#ifndef COMBAT_LOGIC_H_
#define COMBAT_LOGIC_H_

#include <algorithm>

#include "enemy.h"
#include "game_state.h"
#include "player.h"

class CombatLogic {
 public:
  static void ProcessPlayerAction(Player& player, Enemy& enemy, int action);
  static void ProcessEnemyAction(Player& player, Enemy& enemy);

  static double CalculatePurificationChance(Player& player, Enemy& enemy);
  static bool CalculateHit(double attacker_accuracy, double target_evasion);
  static int CalculateDamage(int min_dmg, int max_dmg);

  static void OnEnemyKilled(Player& player, Enemy& enemy, GameState& state);

  static void OnEnemyPurified(Player& player, Enemy& enemy, GameState& state);

  static void ProcessEndOfTurnEffects(Player& player);

  static void ProcessItemDrop(Player& player, Enemy& enemy, GameState& state,
                              const std::string& kill_type);
};

#endif  // COMBAT_LOGIC_H_
