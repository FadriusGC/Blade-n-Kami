#include "combat_system.h"

#include "combat_logic.h"
#include "enemy_factory.h"
#include "game_state.h"
#include "text_view.h"

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

void CombatSystem::InitializeCombat(GameState& state) {
  if (!state.current_enemy_ && state.current_location_->enemy_id_ != "") {
    state.new_enemy_ = new Enemy(
        EnemyFactory::CreateEnemy(state, state.current_location_->enemy_id_));
    state.current_enemy_ = state.new_enemy_;
  }
}

void CombatSystem::HandleCombatResult(CombatResult result, GameState& state) {
  switch (result) {
    case CombatSystem::kPlayerWin:
      state.current_enemy_ = nullptr;
      delete state.new_enemy_;
      state.current_location_->enemy_id_ = "";
      std::cin.ignore();
      state.current_menu_ = MenuState::kGameMenu;
      break;

    case CombatSystem::kEnemyWin:
      TextView::ShowMessage(u8"Игрок погиб, игра окончена :(");
      std::cin.ignore();
      exit(0);

    case CombatSystem::kFlee:
      state.current_menu_ = MenuState::kGameMenu;
      state.current_enemy_ = nullptr;
      delete state.new_enemy_;
      break;
  }
}
