#ifndef BLESSING_ABILITY_HANDLER_H
#define BLESSING_ABILITY_HANDLER_H

#include <functional>
#include <map>
#include <random>

#include "enemy.h"
#include "player.h"
#include "text_view.h"

class BlessingAbilityHandler {
 public:
  using AbilityFunc = std::function<void(Player&, Enemy*, int, int)>;
  static std::map<std::string, AbilityFunc> ability_map_;
  static std::mt19937 gen_;

  static void InitAbilities();

  // Реализации способностей с учетом min и max
  static void Heal(Player& player, Enemy* enemy, int min_power, int max_power);
  static void Damage(Player& player, Enemy* enemy, int minPower, int max_power);
  static void SunStrike(Player& player, Enemy* enemy, int min_power,
                        int max_power);
  static void TouchOfDeath(Player& player, Enemy* enemy, int min_power,
                           int max_power);
  static void RavensFeast(Player& player, Enemy* enemy, int min_power,
                          int max_power);
  static void RuthlessCuts(Player& player, Enemy* enemy, int min_power,
                           int max_power);
  static void DragonTechniqueCalm(Player& player, Enemy* enemy, int min_power,
                                  int max_power);
  static void SacrificialTide(Player& player, Enemy* enemy, int min_power,
                              int max_power);
  static void LunarDance(Player& player, Enemy* enemy, int min_power,
                         int max_power);
  static void PurificationBoost(Player& player, Enemy* enemy, int min_power,
                                int max_power);
  static void ReikiRestore(Player& player, Enemy* enemy, int min_power,
                           int max_power);
};

#endif  // BLESSING_ABILITY_HANDLER_H_
