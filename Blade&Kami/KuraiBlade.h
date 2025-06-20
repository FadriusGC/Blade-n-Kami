// KuraiBlade.h
#pragma once

enum class BladeStatType { DAMAGE, ACCURACY, CRIT, CAPACITY };

class KuraiBlade {
 public:
  int minDamage = 5;
  int maxDamage = 10;
  double accuracy = 0.8;
  double critChance = 0.15;
  int spiritCapacity = 4;

  void upgradeStat(BladeStatType stat);
};
