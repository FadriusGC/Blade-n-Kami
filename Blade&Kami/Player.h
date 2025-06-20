#ifndef PLAYER_H_
#define PLAYER_H_

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
  double max_health_ = 100.0;
  double current_health_ = 100.0;
  double max_reiki_ = 50.0;
  double current_reiki_ = 50.0;
  int available_points_ = 0;
  KuraiBlade blade_;
  std::vector<Blessing> blessings_;

  bool IsAlive() const { return current_health_ > 0; }

  void TakeDamage(int& damage) { current_health_ -= damage; }

  void GainExp(int amount) {  // Модифицировано
    exp_ += amount;
    CheckLevelUp();
  }

  void GainGold(int amount) { gold_ += amount; }

  void CheckLevelUp() {
    while (exp_ >= required_exp_) {
      exp_ -= required_exp_;
      level_++;
      available_points_ += 2;
      required_exp_ = 100 + 50 * level_;
      // Можно добавить TextView::showMessage("Уровень повышен!");
    }
  }
  void IncreaseStat(int stat_type) {
    if (available_points_ <= 0) return;

    switch (stat_type) {
      case 1:
        strength_++;
        break;
      case 2:
        agility_++;
        break;
      case 3:
        spirit_++;
        break;
    }
    available_points_--;
  }

  void Heal(double amount) {
    current_health_ += amount;
    if (current_health_ > max_health_) {
      current_health_ = max_health_;
    }
  }
  void RestoreReiki(double amount) {
    current_reiki_ += amount;
    if (current_reiki_ > max_reiki_) {
      current_reiki_ = max_reiki_;
    }
  }
  void ChangeKi(int delta) {
    ki_ += delta;
    if (ki_ > 100) ki_ = 100;
    if (ki_ < -100) ki_ = -100;
  }

  // Методы для работы с благословениями
  void AddBlessing(const Blessing& blessing) { blessings_.push_back(blessing); }

  void RemoveBlessing(const std::string& blessing_id) {
    blessings_.erase(std::remove_if(blessings_.begin(), blessings_.end(),
                                    [&blessing_id](const Blessing& blessing) {
                                      return blessing.id == blessing_id;
                                    }),
                     blessings_.end());
  }

  bool HasBlessing(const std::string& blessing_id) const {
    for (const auto& blessing : blessings_) {
      if (blessing.id == blessing_id) {
        return true;
      }
    }
    return false;
  }

  std::vector<Blessing> GetActiveBlessings() const {
    std::vector<Blessing> active_blessings;
    for (const auto& blessing : blessings_) {
      if (blessing.type == BlessingType::kActive) {
        active_blessings.push_back(blessing);
      }
    }
    return active_blessings;
  }
};

#endif  // PLAYER_H_
