﻿#include "combat_logic.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>

#include "blessing_system.h"
#include "text_view.h"
float clamp(float value, float min, float max) {
  return std::max(min, std::min(value, max));
}
namespace {
std::mt19937 gen(std::random_device{}());
}

bool CombatLogic::CalculateHit(float acc, float eva) {
  std::uniform_real_distribution<> dis(0.0, 1.0);
  return (dis(gen) <= (acc - eva));
}

int CombatLogic::CalculateDamage(int min, int max) {
  std::uniform_int_distribution<> dis(min, max);
  return dis(gen);
}

double CombatLogic::CalculatePurificationChance(Player& player, Enemy& enemy) {
  double health_factor =
      (1 - (enemy.data_.current_health) / enemy.data_.max_health);
  double player_total = ((player.spirit_ / 20.0) * 0.5 +
                         ((player.blade_.spirit_capacity_ / 20.0) * 0.5));
  double spirit_ratio = (player_total / (enemy.data_.spirit));
  double result = spirit_ratio * 0.4 + health_factor * 0.6;
  return result;
}

void CombatLogic::ProcessPlayerAction(Player& player, Enemy& enemy,
                                      int action) {
  if (action == 1) {  // Атака
    int bonus_damage = 0;
    for (const auto& blessing : player.blessings_) {
      if (blessing.ability == "damage_boost" &&
          blessing.type == BlessingType::kPassive) {
        ModifiedPower power =
            BlessingSystem::CalculateModifiedPower(blessing, player);
        int min_power = power.min;
        int max_power = power.max;
        std::uniform_int_distribution<> dis(min_power, max_power);
        bonus_damage += dis(gen);
      }
    }
    if (CalculateHit(player.blade_.accuracy_, enemy.data_.evasion)) {
      int dmg = CalculateDamage(player.blade_.min_damage_,
                                player.blade_.max_damage_) +
                bonus_damage;
      enemy.TakeDamage(dmg);
      if (bonus_damage > 0) {
        TextView::ShowMessage(u8"🗡️ Вы нанесли " + std::to_string(dmg) + " (" +
                              std::to_string(bonus_damage) +
                              u8" от Благословений)" + u8" урона!");
      } else {
        TextView::ShowMessage(u8"🗡️ Вы нанесли " + std::to_string(dmg) +
                              u8" урона!");
      }
      if (!enemy.IsAlive()) {
        CombatLogic::OnEnemyKilled(player, enemy);
      }

    } else {
      TextView::ShowMessage(u8"💨 Промах!");
      if (!enemy.IsAlive()) {
        CombatLogic::OnEnemyKilled(player, enemy);
      }
    }
  } else if (action == 2) {
    float purification_chance = CalculatePurificationChance(player, enemy);
    std::uniform_real_distribution<> dis(0.0, 1.0);
    if (dis(gen) <= purification_chance) {
      enemy.SetHealth(0);
      CombatLogic::OnEnemyPurified(player, enemy);
    } else {
      TextView::ShowMessage(u8"🖤 Очищение не удалось.");
    }
  } else if (action == 3) {
  }
}

void CombatLogic::ProcessEnemyAction(Player& player, Enemy& enemy) {
  double damage_reduction = 0.0;
  for (const auto& blessing : player.blessings_) {
    if (blessing.ability == "damage_reduction" &&
        blessing.type == BlessingType::kPassive) {
      ModifiedPower power =
          BlessingSystem::CalculateModifiedPower(blessing, player);
      int min_power = power.min;
      int max_power = power.max;
      std::uniform_int_distribution<> dis(min_power, max_power);
      damage_reduction += dis(gen) / 100.0;
    }
  }
  if (CalculateHit(enemy.data_.accuracy, player.evasion_)) {
    int base_dmg =
        CalculateDamage(enemy.data_.min_damage, enemy.data_.max_damage);
    int final_dmg = static_cast<int>(base_dmg * (1.0 - damage_reduction));
    player.TakeDamage(final_dmg);
    if (damage_reduction > 0.0) {
      TextView::ShowMessage(u8"🗡️ " + enemy.data_.name + u8" наносит " +
                            std::to_string(final_dmg) + "/" +
                            std::to_string(base_dmg) + u8" (🛡️ " +
                            std::to_string(base_dmg - final_dmg) +
                            u8" ед. заблокировано) " + u8" урона!");
    } else {
      TextView::ShowMessage(u8"🗡️ " + enemy.data_.name + u8" наносит " +
                            std::to_string(final_dmg) + u8" урона!");
    }
    std::cin.ignore();

  } else {
    TextView::ShowMessage(u8"💨 " + enemy.data_.name + u8" промахнулся!");
    std::cin.ignore();
  }
}

void CombatLogic::OnEnemyKilled(Player& player, Enemy& enemy) {
  int ki_loss = 10 + (enemy.data_.spirit / 2);
  std::uniform_real_distribution<> random_reward(
      enemy.data_.gold_reward - enemy.data_.gold_reward * 0.2,
      enemy.data_.gold_reward * 1.2);
  int gold_reward = random_reward(gen);
  player.ChangeKi(-ki_loss);
  TextView::ShowWinMessage(u8"====🏆Победа🏆====\n🌟 Опыт +" +
                           std::to_string(enemy.data_.exp_reward) + u8"\n" +
                           u8"💰 Мон Души: +" + std::to_string(gold_reward) +
                           u8"\n🌑 Ки изменилось на " +
                           std::to_string(-ki_loss) + u8"\n==================");
  player.GainExp(enemy.data_.exp_reward);
  player.GainGold(gold_reward);
}

void CombatLogic::OnEnemyPurified(Player& player, Enemy& enemy) {
  int ki_gain = 15 + (enemy.data_.spirit / 2);
  std::uniform_real_distribution<> random_reward(
      enemy.data_.gold_reward - enemy.data_.gold_reward * 0.2,
      enemy.data_.gold_reward * 1.2);
  int gold_reward = random_reward(gen);
  player.ChangeKi(ki_gain);
  TextView::ShowWinMessage(u8"====🏆Победа🏆====\n🤍 Вы успешно Очистили " +
                           enemy.data_.name + u8"!" + u8"\n🌟 Опыт +" +
                           std::to_string(enemy.data_.exp_reward) + u8"\n" +
                           u8"💰 Мон Души: +" + std::to_string(gold_reward) +
                           u8"\n🌕 Ки изменилось на +" +
                           std::to_string(ki_gain) + u8"\n==================");
  player.GainExp(enemy.data_.exp_reward);
  player.GainGold(gold_reward);
}

void CombatLogic::ProcessEndOfTurnEffects(Player& player) {
  for (const auto& blessing : player.blessings_) {
    if (blessing.type == BlessingType::kPassive) {
      if (blessing.ability == "regeneration") {
        ModifiedPower power =
            BlessingSystem::CalculateModifiedPower(blessing, player);
        int min_power = power.min;
        int max_power = power.max;
        std::uniform_int_distribution<> dis(min_power, max_power);
        int heal_value = dis(gen);
        player.Heal(heal_value);
        TextView::ShowMessage(u8"🌞 Неугасимый свет: восстановлено " +
                              std::to_string(heal_value) + u8" здоровья.");
      } else if (blessing.ability == "full_moon") {
        ModifiedPower power =
            BlessingSystem::CalculateModifiedPower(blessing, player);
        int min_power = power.min;
        int max_power = power.max;
        std::uniform_int_distribution<> dis(min_power, max_power);
        int restore_value = dis(gen);
        player.RestoreReiki(restore_value);
        TextView::ShowMessage(u8"🌕 Полнолуние: восстановлено " +
                              std::to_string(restore_value) + u8" Рэйки.");
      }
    }
  }
}
