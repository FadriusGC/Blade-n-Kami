#include "blessing_ability_handler.h"

#include <random>

std::map<std::string, BlessingAbilityHandler::AbilityFunc>
    BlessingAbilityHandler::ability_map_;
std::mt19937 BlessingAbilityHandler::gen_(std::random_device{}());

void BlessingAbilityHandler::InitAbilities() {
  ability_map_["heal"] = &Heal;
  ability_map_["damage"] = &Damage;
  ability_map_["sun_strike"] = &SunStrike;
  ability_map_["touch_of_death"] = &TouchOfDeath;
  ability_map_["ravens_feast"] = &RavensFeast;
  ability_map_["ruthless_cuts"] = &RuthlessCuts;
  ability_map_["dragon_technique_calm"] = &DragonTechniqueCalm;
  ability_map_["sacrificial_tide"] = &SacrificialTide;
  ability_map_["lunar_dance"] = &LunarDance;
  ability_map_["purification_boost"] = &PurificationBoost;
  ability_map_["reiki_restore"] = &ReikiRestore;
}

void BlessingAbilityHandler::Heal(Player& player, Enemy* enemy, int min_power,
                                  int max_power) {
  std::uniform_int_distribution<> dis(min_power, max_power);
  int heal_value = dis(gen_);
  player.Heal(heal_value);
  TextView::ShowMessage(u8"💚 Восстановлено " + std::to_string(heal_value) +
                        u8" здоровья!");
}

void BlessingAbilityHandler::Damage(Player& player, Enemy* enemy, int min_power,
                                    int max_power) {
  if (!enemy) return;
  std::uniform_int_distribution<> dis(min_power, max_power);
  int damage = dis(gen_);
  enemy->TakeDamage(damage);
  TextView::ShowMessage(u8"🗡️ Нанесено " + std::to_string(damage) +
                        u8" урона!");
}

void BlessingAbilityHandler::ReikiRestore(Player& player, Enemy* enemy,
                                          int min_power, int max_power) {
  std::uniform_int_distribution<> dis(min_power, max_power);
  int reiki_value = dis(gen_);
  player.current_reiki_ += reiki_value;
  if (player.current_reiki_ > player.max_reiki_)
    player.current_reiki_ = player.max_reiki_;
  TextView::ShowMessage(u8"🌀 Восстановлено " + std::to_string(reiki_value) +
                        u8" Рэйки!");
}

void BlessingAbilityHandler::SunStrike(Player& player, Enemy* enemy,
                                       int min_power, int max_power) {
  if (!enemy) return;
  std::uniform_int_distribution<> dis(min_power, max_power);
  int base_damage = dis(gen_);
  int bonus_damage = static_cast<int>(player.max_health_ * 0.1);
  int total_damage = base_damage + bonus_damage;
  enemy->TakeDamage(total_damage);
  TextView::ShowMessage(u8"☀️ Удар солнца наносит " +
                        std::to_string(total_damage) + u8" урона! (" +
                        std::to_string(bonus_damage) + u8" от здоровья)");
}

void BlessingAbilityHandler::TouchOfDeath(Player& player, Enemy* enemy,
                                          int min_power, int max_power) {
  if (!enemy) return;
  std::uniform_int_distribution<> dis(min_power, max_power);
  int base_damage = dis(gen_);
  double missing_health_ratio =
      1.0 - (enemy->data_.current_health / enemy->data_.max_health);
  int bonus_damage =
      static_cast<int>(missing_health_ratio * enemy->data_.max_health * 0.3);
  int total_damage = base_damage + bonus_damage;
  enemy->TakeDamage(total_damage);
  TextView::ShowMessage(u8"☠️ Прикосновение смерти наносит " +
                        std::to_string(total_damage) + u8" урона! (" +
                        std::to_string(bonus_damage) +
                        u8" от недостающего здоровья)");
}

void BlessingAbilityHandler::RavensFeast(Player& player, Enemy* enemy,
                                         int min_power, int max_power) {
  if (!enemy) return;
  std::uniform_int_distribution<> dis(min_power, max_power);
  int base_damage = dis(gen_);
  enemy->TakeDamage(base_damage);
  int heal_value = static_cast<int>(base_damage * 0.3);
  player.Heal(heal_value);
  TextView::ShowMessage(
      u8"🦅 Пиршество ворона наносит " + std::to_string(base_damage) +
      u8" урона и исцеляет вас на " + std::to_string(heal_value) + u8"!");
}

void BlessingAbilityHandler::RuthlessCuts(Player& player, Enemy* enemy,
                                          int min_power, int max_power) {
  if (!enemy) return;
  std::uniform_int_distribution<> dis(min_power, max_power);
  int base_damage = dis(gen_);
  double missing_health_ratio =
      1.0 - (player.current_health_ / player.max_health_);
  int bonus_damage =
      static_cast<int>(missing_health_ratio * player.max_health_ * 0.2);
  int total_damage = base_damage + bonus_damage;
  enemy->TakeDamage(total_damage);
  TextView::ShowMessage(u8"🔪 Безжалостные разрезы наносят " +
                        std::to_string(total_damage) + u8" урона! (" +
                        std::to_string(bonus_damage) +
                        u8" от вашего недостающего здоровья)");
}

void BlessingAbilityHandler::DragonTechniqueCalm(Player& player, Enemy* enemy,
                                                 int min_power, int max_power) {
  if (!enemy) return;
  int base_damage = min_power;
  int reiki_spent = player.current_reiki_;
  player.current_reiki_ = 0;
  int bonus_damage = static_cast<int>(reiki_spent * 0.5);
  int total_damage = base_damage + bonus_damage;
  enemy->TakeDamage(total_damage);
  TextView::ShowMessage(u8"🐉 Драконья Техника: Штиль наносит " +
                        std::to_string(total_damage) + u8" урона! (Потрачено " +
                        std::to_string(reiki_spent) + u8" Рэйки)");
}

void BlessingAbilityHandler::SacrificialTide(Player& player, Enemy* enemy,
                                             int min_power, int max_power) {
  double health_cost = player.current_health_ * 0.1;
  static_cast<int>(health_cost);
  player.current_health_ -= health_cost;
  std::uniform_int_distribution<> dis(min_power, max_power);
  int reiki_gain = dis(gen_);
  player.current_reiki_ += reiki_gain;
  if (player.current_reiki_ > player.max_reiki_)
    player.current_reiki_ = player.max_reiki_;
  TextView::ShowMessage(u8"💧 Жертвенный прилив: вы теряете " +
                        std::to_string(static_cast<int>(health_cost)) +
                        u8" здоровья и восстанавливаете " +
                        std::to_string(reiki_gain) + u8" Рэйки!");
}

void BlessingAbilityHandler::LunarDance(Player& player, Enemy* enemy,
                                        int min_power, int max_power) {
  if (!enemy) return;
  std::uniform_int_distribution<> dis(min_power, max_power);
  int base_damage = dis(gen_);
  int bonus_damage = static_cast<int>(player.max_reiki_ * 0.2);
  int total_damage = base_damage + bonus_damage;
  enemy->TakeDamage(total_damage);
  TextView::ShowMessage(u8"🌙 Танец луны наносит " +
                        std::to_string(total_damage) + u8" урона! (" +
                        std::to_string(bonus_damage) +
                        u8" от вашей максимальной Рэйки)");
}

void BlessingAbilityHandler::PurificationBoost(Player& p, Enemy* enemy,
                                               int min_power, int max_power) {
  TextView::ShowMessage(u8"🤍 Сила очищения увеличена!");
}
