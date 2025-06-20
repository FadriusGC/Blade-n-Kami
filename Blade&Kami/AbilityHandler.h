// AbilityHandler.h
#ifndef ABILITY_HANDLER_H_
#define ABILITY_HANDLER_H_

#include <functional>
#include <map>
#include <random>

#include "Enemy.h"
#include "Item.h"
#include "Player.h"

class AbilityHandler {
 public:
  using AbilityFunc = std::function<void(Player&, Enemy*, int, int)>;

  static void initAbilities();
  static void execute(const Item& item, Player& player, Enemy* enemy);

  static void damage(Player& p, Enemy* e, int min, int max);

  static void heal(Player& p, Enemy* e, int min, int max);

 private:
  static std::map<std::string, AbilityFunc> abilityMap;
  static std::mt19937 gen;
};

#endif  // ABILITY_HANDLER_H_
