#include "player.h"

#include <algorithm>
#include <vector>

#include "blessing.h"

bool Player::IsAlive() const { return current_health_ > 0; }

void Player::TakeDamage(int damage) { current_health_ -= damage; }

void Player::GainExp(int amount) {
  exp_ += amount;
  CheckLevelUp();
}

void Player::GainGold(int amount) { gold_ += amount; }

void Player::CheckLevelUp() {
  while (exp_ >= required_exp_) {
    exp_ -= required_exp_;
    level_++;
    available_points_ += 2;
    required_exp_ = 100 + 50 * level_;
  }
}

void Player::IncreaseStat(int stat_type) {
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
  RecalculateStats();
}

void Player::Heal(double amount) {
  current_health_ += amount;
  if (current_health_ > max_health_) {
    current_health_ = max_health_;
  }
}

void Player::RestoreReiki(double amount) {
  current_reiki_ += amount;
  if (current_reiki_ > max_reiki_) {
    current_reiki_ = max_reiki_;
  }
}

void Player::ChangeKi(int delta) {
  ki_ += delta;
  if (ki_ > 100) ki_ = 100;
  if (ki_ < -100) ki_ = -100;
}

void Player::AddBlessing(const Blessing& blessing) {
  blessings_.push_back(blessing);
}

void Player::RemoveBlessing(const std::string& blessing_id) {
  blessings_.erase(
      std::remove_if(blessings_.begin(), blessings_.end(),
                     [&](const Blessing& b) { return b.id == blessing_id; }),
      blessings_.end());
}

bool Player::HasBlessing(const std::string& blessing_id) const {
  for (const auto& blessing : blessings_) {
    if (blessing.id == blessing_id) return true;
  }
  return false;
}

std::vector<Blessing> Player::GetActiveBlessings() const {
  std::vector<Blessing> active;
  for (const auto& blessing : blessings_) {
    if (blessing.type == BlessingType::kActive) {
      active.push_back(blessing);
    }
  }
  return active;
}

void Player::ClearBlessings() { blessings_.clear(); }

double Player::GetMaxHealth() const {
  return base_health_ + (strength_ - 5) * 15.0;
}

double Player::GetMaxReiki() const {
  return base_reiki_ + (spirit_ - 5) * 10.0;
}

double Player::GetEvasion() const {
  return (std::min)(0.95, 0.1 + (agility_ - 5) * 0.02);
}

double Player::GetAccuracy() const {
  return (std::min)(0.98, blade_.accuracy_ + (agility_ - 5) * 0.01);
}

int Player::GetMinDamage() const {
  return blade_.min_damage_ + GetStrengthDamageBonus();
}

int Player::GetMaxDamage() const {
  return blade_.max_damage_ + GetStrengthDamageBonus();
}

int Player::GetStrengthDamageBonus() const { return (strength_ - 5) * 1.5; }

void Player::RecalculateStats() {
  double old_max_health = max_health_;
  double old_max_reiki = max_reiki_;

  max_health_ = GetMaxHealth();
  max_reiki_ = GetMaxReiki();

  current_health_ += (max_health_ - old_max_health);
  current_reiki_ += (max_reiki_ - old_max_reiki);

  if (current_health_ > max_health_) current_health_ = max_health_;
  if (current_reiki_ > max_reiki_) current_reiki_ = max_reiki_;

  evasion_ = GetEvasion();
}
