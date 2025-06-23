#include "kurai_blade.h"

#include <algorithm>

void KuraiBlade::upgradeStat(BladeStatType stat) {
  switch (stat) {
    case BladeStatType::kDamage:
      min_damage_ += 2;
      max_damage_ += 3;
      break;

    case BladeStatType::kAccuracy:
      accuracy_ = std::min(0.95, accuracy_ + 0.07);
      break;

    case BladeStatType::kCrit:
      crit_chance_ = std::min(0.50, crit_chance_ + 0.02);
      break;

    case BladeStatType::kCapacity:
      spirit_capacity_ += 5;
      break;
  }
}
