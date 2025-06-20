#pragma once
#include <functional>
#include <map>
#include <random>

#include "Enemy.h"
#include "Player.h"
#include "TextView.h"

class BlessingAbilityHandler {
 public:
  using AbilityFunc = std::function<void(Player&, Enemy*, int, int)>;
  static std::map<std::string, AbilityFunc> abilityMap;
  static std::mt19937 gen;

  static void initAbilities();

  // Реализации способностей с учетом min и max
  static void heal(Player& p, Enemy* e, int minPower, int maxPower);
  static void damage(Player& p, Enemy* e, int minPower, int maxPower);
  static void sunStrike(Player& p, Enemy* e, int minPower, int maxPower);
  static void touchOfDeath(Player& p, Enemy* e, int minPower, int maxPower);
  static void ravensFeast(Player& p, Enemy* e, int minPower, int maxPower);
  static void ruthlessCuts(Player& p, Enemy* e, int minPower, int maxPower);
  static void dragonTechniqueCalm(Player& p, Enemy* e, int minPower,
                                  int maxPower);
  static void sacrificialTide(Player& p, Enemy* e, int minPower, int maxPower);
  static void lunarDance(Player& p, Enemy* e, int minPower, int maxPower);
  static void purificationBoost(Player& p, Enemy* e, int minPower,
                                int maxPower);
  static void reikiRestore(Player& p, Enemy* e, int minPower, int maxPower);
};
