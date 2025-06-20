#ifndef KURAI_BLADE_H_
#define KURAI_BLADE_H_

enum class BladeStatType { kDamage, kAccuracy, kCrit, kCapacity };

class KuraiBlade {
 public:
  int min_damage_ = 5;
  int max_damage_ = 10;
  double accuracy_ = 0.8;
  double crit_chance_ = 0.15;
  int spirit_capacity_ = 4;

  void upgradeStat(BladeStatType stat);
};

#endif  // KURAI_BLADE_H_
