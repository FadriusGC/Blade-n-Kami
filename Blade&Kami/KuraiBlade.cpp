#include "KuraiBlade.h"

#include <algorithm>

void KuraiBlade::upgradeStat(BladeStatType stat) {
  switch (stat) {
    case BladeStatType::DAMAGE:
      minDamage += 2;
      maxDamage += 3;
      break;

    case BladeStatType::ACCURACY:
      accuracy = std::min(0.95, accuracy + 0.07);
      break;

    case BladeStatType::CRIT:
      critChance = std::min(0.35, critChance + 0.05);
      break;

    case BladeStatType::CAPACITY:
      spiritCapacity += 5;
      break;
  }
}
