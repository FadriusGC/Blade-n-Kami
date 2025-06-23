#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include "blessing_system.h"
#include "combat_system.h"
#include "game_state.h"

class GameController {
  GameState* state_;

 public:
  explicit GameController(GameState* state_) : state_(state_) {}

  bool HandleMainMenu(int choice);
  bool HandleGameMenu(int choice);
  void HandleLocationMenu(int choice);
  void HandleLocationExplore();
  bool HandleMovement(int targetId);
  void HandlePlayerMenu(int choice);
  void HandleLevelUpMenu(int choice);
  void HandleKuraiMenu(int choice);
  CombatSystem::CombatResult HandleCombatMenu(int choice, Enemy& enemy);
  void HandleItemUse(int itemIndex);
  void HandleInventoryMenu(int choice);
  void HandleInventoryCombatMenu(int choice);
  void HandleAltarMenu(int choice);
  void HandleBlessingCombatMenu(int choice);
  void HandleBlessingMenu(int choice);

  static void HandleGameEnding(GameEnding& ending, GameState& state);
  static GameEnding DetermineEnding(GameState& state);
};

#endif  // GAME_CONTROLLER_H_
