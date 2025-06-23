#ifndef COMBAT_SYSTEM_H_
#define COMBAT_SYSTEM_H_

#include "enemy.h"
#include "game_state.h"
#include "player.h"

class CombatSystem {
 public:
  enum CombatResult { kInProgress, kPlayerWin, kEnemyWin, kFlee };

  static CombatResult UpdateCombat(Player& player, Enemy& enemy,
                                   int player_action, GameState& state);

  static void InitializeCombat(GameState& state);
  static void HandleCombatResult(CombatResult result, GameState& state);
};

#endif  // COMBAT_SYSTEM_H_
