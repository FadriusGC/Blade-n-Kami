#ifndef ABILITY_HANDLER_H_
#define ABILITY_HANDLER_H_

#include <functional>
#include <map>
#include <random>

#include "enemy.h"
#include "item.h"
#include "player.h"

class AbilityHandler {
 public:
  using AbilityFunc = std::function<void(Player&, Enemy*, int, int)>;

  static void InitAbilities();
  static void Execute(const Item& item, Player& player, Enemy* enemy);

  static void Damage(Player& p, Enemy* e, int min, int max);

  static void Heal(Player& p, Enemy* e, int min, int max);

 private:
  static std::map<std::string, AbilityFunc> AbilityMap_;
  static std::mt19937 gen_;
};

#endif  // ABILITY_HANDLER_H_
