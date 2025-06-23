#include "combat_system.h"

#include "combat_logic.h"
#include "game_state.h"

CombatSystem::CombatResult CombatSystem::UpdateCombat(Player& player,
                                                      Enemy& enemy,
                                                      int player_action,
                                                      GameState& state) {
  // Обработка действия игрока
  CombatLogic::ProcessPlayerAction(player, enemy, player_action);
  if (!enemy.IsAlive()) {
    // Проверяем, было ли это очищение или убийство
    if (player_action == 2) {
      CombatLogic::OnEnemyPurified(player, enemy, state);
    } else {
      CombatLogic::OnEnemyKilled(player, enemy, state);
    }
    return kPlayerWin;
  }

  // Обработка действия врага
  CombatLogic::ProcessEnemyAction(player, enemy);
  if (!player.IsAlive()) return kEnemyWin;

  CombatLogic::ProcessEndOfTurnEffects(player);
  if (!enemy.IsAlive()) return kPlayerWin;
  if (!player.IsAlive()) return kEnemyWin;

  return kInProgress;
}
