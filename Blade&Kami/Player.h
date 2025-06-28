#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <vector>

#include "blessing.h"
#include "kurai_blade.h"

class Player {
 public:
  int level_ = 1;
  int exp_ = 0;
  int required_exp_ = 100 + 50 * level_;
  int gold_ = 0;
  int ki_ = 0;
  int strength_ = 5;
  int agility_ = 5;
  int spirit_ = 5;
  double evasion_ = 0.1;
  double base_health_ = 100.0;
  double max_health_ = base_health_;
  double current_health_ = 100.0;
  double base_reiki_ = 50.0;
  double max_reiki_ = base_reiki_;
  double current_reiki_ = 50.0;
  int available_points_ = 0;
  KuraiBlade blade_;
  std::vector<Blessing> blessings_;

  bool IsAlive() const;

  void TakeDamage(int damage);

  void GainExp(int amount);

  void GainGold(int amount);

  void CheckLevelUp();

  void IncreaseStat(int stat_type);

  void Heal(double amount);

  void RestoreReiki(double amount);

  void ChangeKi(int delta);

  void AddBlessing(const Blessing& blessing);

  void RemoveBlessing(const std::string& blessing_id);

  bool HasBlessing(const std::string& blessing_id) const;

  std::vector<Blessing> GetActiveBlessings() const;

  void ClearBlessings();

  double GetMaxHealth() const;

  double GetMaxReiki() const;

  double GetEvasion() const;

  double GetAccuracy() const;

  int GetMinDamage() const;

  int GetMaxDamage() const;

  int GetStrengthDamageBonus() const;

  void RecalculateStats();
};

#endif  // PLAYER_H_
