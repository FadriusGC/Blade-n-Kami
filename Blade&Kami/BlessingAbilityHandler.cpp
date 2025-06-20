#include "BlessingAbilityHandler.h"

#include <random>

std::map<std::string, BlessingAbilityHandler::AbilityFunc>
    BlessingAbilityHandler::abilityMap;
std::mt19937 BlessingAbilityHandler::gen(std::random_device{}());

void BlessingAbilityHandler::initAbilities() {
  abilityMap["heal"] = &heal;
  abilityMap["damage"] = &damage;
  abilityMap["sun_strike"] = &sunStrike;
  abilityMap["touch_of_death"] = &touchOfDeath;
  abilityMap["ravens_feast"] = &ravensFeast;
  abilityMap["ruthless_cuts"] = &ruthlessCuts;
  abilityMap["dragon_technique_calm"] = &dragonTechniqueCalm;
  abilityMap["sacrificial_tide"] = &sacrificialTide;
  abilityMap["lunar_dance"] = &lunarDance;
  abilityMap["purification_boost"] = &purificationBoost;
  abilityMap["reiki_restore"] = &reikiRestore;
}

// Реализации с учетом min/max и расхода Рэйки
void BlessingAbilityHandler::heal(Player& p, Enemy* e, int minPower,
                                  int maxPower) {
  std::uniform_int_distribution<> dis(minPower, maxPower);
  int healValue = dis(gen);
  p.heal(healValue);
  TextView::showMessage(u8"💚 Восстановлено " + std::to_string(healValue) +
                        u8" здоровья!");
}

void BlessingAbilityHandler::damage(Player& p, Enemy* e, int minPower,
                                    int maxPower) {
  if (!e) return;
  std::uniform_int_distribution<> dis(minPower, maxPower);
  int damage = dis(gen);
  e->takeDamage(damage);
  TextView::showMessage(u8"🗡️ Нанесено " + std::to_string(damage) +
                        u8" урона!");
}

void BlessingAbilityHandler::reikiRestore(Player& p, Enemy* e, int minPower,
                                          int maxPower) {
  std::uniform_int_distribution<> dis(minPower, maxPower);
  int reikiValue = dis(gen);
  p.currentReiki += reikiValue;
  if (p.currentReiki > p.maxReiki) p.currentReiki = p.maxReiki;
  TextView::showMessage(u8"🌀 Восстановлено " + std::to_string(reikiValue) +
                        u8" Рэйки!");
}

void BlessingAbilityHandler::sunStrike(Player& p, Enemy* e, int minPower,
                                       int maxPower) {
  if (!e) return;
  std::uniform_int_distribution<> dis(minPower, maxPower);
  int baseDamage = dis(gen);
  int bonusDamage = static_cast<int>(p.maxHealth * 0.1);
  int totalDamage = baseDamage + bonusDamage;
  e->takeDamage(totalDamage);
  TextView::showMessage(u8"☀️ Удар солнца наносит " +
                        std::to_string(totalDamage) + u8" урона! (" +
                        std::to_string(bonusDamage) + u8" от здоровья)");
}

void BlessingAbilityHandler::touchOfDeath(Player& p, Enemy* e, int minPower,
                                          int maxPower) {
  if (!e) return;
  std::uniform_int_distribution<> dis(minPower, maxPower);
  int baseDamage = dis(gen);
  double missingHealthRatio = 1.0 - (e->data.currentHealth / e->data.maxHealth);
  int bonusDamage =
      static_cast<int>(missingHealthRatio * e->data.maxHealth * 0.3);
  int totalDamage = baseDamage + bonusDamage;
  e->takeDamage(totalDamage);
  TextView::showMessage(u8"☠️ Прикосновение смерти наносит " +
                        std::to_string(totalDamage) + u8" урона! (" +
                        std::to_string(bonusDamage) +
                        u8" от недостающего здоровья)");
}

void BlessingAbilityHandler::ravensFeast(Player& p, Enemy* e, int minPower,
                                         int maxPower) {
  if (!e) return;
  std::uniform_int_distribution<> dis(minPower, maxPower);
  int baseDamage = dis(gen);
  e->takeDamage(baseDamage);
  int healValue = static_cast<int>(baseDamage * 0.3);
  p.heal(healValue);
  TextView::showMessage(
      u8"🦅 Пиршество ворона наносит " + std::to_string(baseDamage) +
      u8" урона и исцеляет вас на " + std::to_string(healValue) + u8"!");
}

void BlessingAbilityHandler::ruthlessCuts(Player& p, Enemy* e, int minPower,
                                          int maxPower) {
  if (!e) return;
  std::uniform_int_distribution<> dis(minPower, maxPower);
  int baseDamage = dis(gen);
  double missingHealthRatio = 1.0 - (p.currentHealth / p.maxHealth);
  int bonusDamage = static_cast<int>(missingHealthRatio * p.maxHealth * 0.2);
  int totalDamage = baseDamage + bonusDamage;
  e->takeDamage(totalDamage);
  TextView::showMessage(u8"🔪 Безжалостные разрезы наносят " +
                        std::to_string(totalDamage) + u8" урона! (" +
                        std::to_string(bonusDamage) +
                        u8" от вашего недостающего здоровья)");
}

void BlessingAbilityHandler::dragonTechniqueCalm(Player& p, Enemy* e,
                                                 int minPower, int maxPower) {
  if (!e) return;
  int baseDamage = minPower;  // Фиксированное минимальное значение
  int reikiSpent = p.currentReiki;
  p.currentReiki = 0;
  int bonusDamage = static_cast<int>(reikiSpent * 0.5);
  int totalDamage = baseDamage + bonusDamage;
  e->takeDamage(totalDamage);
  TextView::showMessage(u8"🐉 Драконья Техника: Штиль наносит " +
                        std::to_string(totalDamage) + u8" урона! (Потрачено " +
                        std::to_string(reikiSpent) + u8" Рэйки)");
}

void BlessingAbilityHandler::sacrificialTide(Player& p, Enemy* e, int minPower,
                                             int maxPower) {
  double healthCost = p.currentHealth * 0.1;
  static_cast<int>(healthCost);
  p.currentHealth -= healthCost;
  std::uniform_int_distribution<> dis(minPower, maxPower);
  int reikiGain = dis(gen);
  p.currentReiki += reikiGain;
  if (p.currentReiki > p.maxReiki) p.currentReiki = p.maxReiki;
  TextView::showMessage(u8"💧 Жертвенный прилив: вы теряете " +
                        std::to_string(static_cast<int>(healthCost)) +
                        u8" здоровья и восстанавливаете " +
                        std::to_string(reikiGain) + u8" Рэйки!");
}

void BlessingAbilityHandler::lunarDance(Player& p, Enemy* e, int minPower,
                                        int maxPower) {
  if (!e) return;
  std::uniform_int_distribution<> dis(minPower, maxPower);
  int baseDamage = dis(gen);
  int bonusDamage = static_cast<int>(p.maxReiki * 0.2);
  int totalDamage = baseDamage + bonusDamage;
  e->takeDamage(totalDamage);
  TextView::showMessage(
      u8"🌙 Танец луны наносит " + std::to_string(totalDamage) + u8" урона! (" +
      std::to_string(bonusDamage) + u8" от вашей максимальной Рэйки)");
}

void BlessingAbilityHandler::purificationBoost(Player& p, Enemy* e,
                                               int minPower, int maxPower) {
  // Логика будет в CombatLogic
  TextView::showMessage(u8"🤍 Сила очищения увеличена!");
}
