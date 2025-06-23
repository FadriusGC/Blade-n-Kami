#ifndef TEXTVIEW_H_
#define TEXTVIEW_H_

#include <iostream>
#include <string>

#include "game_state.h"

class TextView {
 public:
  static void ClearScreen();
  static void ShowMainMenu();
  static void ShowGameMenu();
  static void ShowLocation(const Location& loc);
  static void ShowAvailableConnections(const GameState& state);
  static void ShowMessage(const std::string& msg);
  static void ShowWinMessage(const std::string& msg);
  static void ShowPlayerMenu(const Player& player);

  static void ShowKiBar(int kiValue);

  static std::string GenerateKiBar(int kiValue);

  static void ShowKuraiMenu(const KuraiBlade& blade);
  static void ShowLevelUpMenu(const Player& player);
  static void ShowEnemyInfo(const Enemy& enemy);
  static void ShowEnemyList(const std::vector<EnemyData>& enemies);
  static void ShowEnemyDetails(const Enemy& enemy);
  static void ShowCombatStats(const Player& player, const Enemy& enemy);
  static void ShowCombatMenu(Player& player, Enemy& enemy);
  static void ShowInventory(const Inventory& inv);
  static void ShowInventoryCombat(const Inventory& inv);

  static void ShowLocationMenu(const Location& loc);
  static void ShowLocationDetails(const Location& loc);
  static void ShowChestInteraction(int gold_found,
                                   const std::string dropped_item);

  static void ShowAltarMenu(const std::vector<Blessing>& available_blessings,
                            const Player& player);
  static void ShowBlessingMenu(const std::vector<Blessing>& blessings,
                               const Player& player);
  static void ShowBlessingDetails(const Blessing& blessing,
                                  const Player& player);
  static void ShowCombatBlessingsMenu(
      const std::vector<Blessing>& active_blessings, const Player& player);
  static std::string WrapText(const std::string& text, int width = 90);

  static std::string GeneratePowerDescription(const std::string& ability,
                                              int min_power, int max_power);

  static void ShowEvilEnding(GameState& state);
  static void ShowGoodEnding(GameState& state);
  static void ShowBloodAndSakeEnding(GameState& state);
};

#endif  // TEXTVIEW_H_
