// CombatSystem.cpp
#include "CombatSystem.h"

#include "CombatLogic.h"

CombatSystem::CombatResult CombatSystem::updateCombat(Player& player,
                                                      Enemy& enemy,
                                                      int playerAction,
                                                      GameState& state) {
  // Обработка действия игрока
  CombatLogic::processPlayerAction(player, enemy, playerAction);
  if (!enemy.isAlive()) return PLAYER_WIN;

  // Обработка действия врага
  CombatLogic::processEnemyAction(player, enemy);
  if (!player.isAlive()) return ENEMY_WIN;

  CombatLogic::processEndOfTurnEffects(player);
  if (!enemy.isAlive()) return PLAYER_WIN;
  if (!player.isAlive()) return ENEMY_WIN;

  return IN_PROGRESS;
}
