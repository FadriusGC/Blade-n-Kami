#ifndef BLESSING_SYSTEM_H_
#define BLESSING_SYSTEM_H_

#include <random>
#include <vector>

#include "blessing.h"
#include "enemy.h"
#include "player.h"

struct ModifiedPower {
  int min;
  int max;
};

class BlessingSystem {
 private:
  static std::mt19937 gen_;

 public:
  static void InitBlessings();

  static std::string GetKamiType(const Blessing& blessing);
  static std::vector<Blessing> GetRandomBlessings(
      const std::vector<Blessing>& all_blessings,
      const std::vector<Blessing>& player_blessings, int count = 3);
  static ModifiedPower CalculateModifiedPower(const Blessing& blessing,
                                              const Player& player);
  static bool CanUseBlessing(const Blessing& blessing, const Player& player);
  static void ExecuteBlessing(const Blessing& blessing, Player& player,
                              Enemy* enemy = nullptr);
  static void ApplyPassiveBlessings(Player& player,
                                    const std::vector<Blessing>& blessings);
};

#endif  // BLESSING_SYSTEM_H_
