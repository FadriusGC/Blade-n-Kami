#include "blessing_system.h"

#include <algorithm>
#include <random>

#include "ability_handler.h"
#include "blessing_ability_handler.h"
#include "text_view.h"
std::mt19937 BlessingSystem::gen_(std::random_device{}());

std::string BlessingSystem::GetKamiType(const Blessing& blessing) {
  if (blessing.kami_type == u8"good") {
    return u8"Свет";
  } else if (blessing.kami_type == u8"evil") {
    return u8"Тьма";
  }
}

std::vector<Blessing> BlessingSystem::GetRandomBlessings(
    const std::vector<Blessing>& all_blessings,
    const std::vector<Blessing>& player_blessings, int count) {
  std::vector<Blessing> available_blessings;

  for (const auto& blessing : all_blessings) {
    bool has_blessing = false;
    for (const auto& player_blessing : player_blessings) {
      if (player_blessing.id == blessing.id) {
        has_blessing = true;
        break;
      }
    }
    if (!has_blessing) {
      available_blessings.push_back(blessing);
    }
  }

  if (available_blessings.size() <= count) {
    return available_blessings;
  }

  std::vector<Blessing> selected_blessings;
  std::shuffle(available_blessings.begin(), available_blessings.end(), gen_);

  for (int i = 0; i < count && i < available_blessings.size(); ++i) {
    selected_blessings.push_back(available_blessings[i]);
  }

  return selected_blessings;
}

bool BlessingSystem::CanUseBlessing(const Blessing& blessing,
                                    const Player& player) {
  if (blessing.type == BlessingType::kPassive) {
    return true;
  }

  return player.current_reiki_ >= blessing.reiki_cost;
}
void BlessingSystem::ApplyPassiveBlessings(
    Player& player, const std::vector<Blessing>& blessings) {
  for (const auto& blessing : blessings) {
    if (blessing.type == BlessingType::kPassive) {
      ModifiedPower power = CalculateModifiedPower(blessing, player);
      int avg_power = (power.min + power.max) / 2;

      if (blessing.ability == "health_boost") {
        player.base_health_ += avg_power;
        player.current_health_ += avg_power;
        player.RecalculateStats();
        TextView::ShowMessage(
            u8"❤️ Максимальное здоровье увеличено на " +
            std::to_string(static_cast<int>(avg_power)) + "!\n" +
            u8"       Текущее здоровье: " +
            std::to_string(static_cast<int>(player.current_health_)) + "/" +
            std::to_string(static_cast<int>(player.max_health_)));

      } else if (blessing.ability == "reiki_boost") {
        player.base_reiki_ += avg_power;
        player.current_reiki_ += avg_power;
        player.RecalculateStats();
        TextView::ShowMessage(
            u8"🌀 Максимальное Рэйки увеличено на " +
            std::to_string(static_cast<int>(avg_power)) + "!\n" +
            u8"       Текущее Рэйки: " +
            std::to_string(static_cast<int>(player.current_reiki_)) + "/" +
            std::to_string(static_cast<int>(player.max_reiki_)));

      } else if (blessing.ability == "strength_boost") {
        player.strength_ += avg_power;
        TextView::ShowMessage(u8"💪 Сила увеличена на " +
                              std::to_string(avg_power) + "!");
        player.RecalculateStats();

      } else if (blessing.ability == "agility_boost") {
        player.agility_ += avg_power;
        TextView::ShowMessage(u8"🏹 Ловкость увеличена на " +
                              std::to_string(avg_power) + "!");
        player.RecalculateStats();

      } else if (blessing.ability == "spirit_boost") {
        player.spirit_ += avg_power;
        TextView::ShowMessage(u8"🧿 Дух увеличен на " +
                              std::to_string(avg_power) + "!");
        player.RecalculateStats();

      } else if (blessing.ability == "golden_grace") {
        player.base_health_ += avg_power;
        player.current_health_ += avg_power;
        player.RecalculateStats();
        TextView::ShowMessage(
            u8"❤️ Максимальное здоровье увеличено на " +
            std::to_string(static_cast<int>(avg_power)) + "!\n" +
            u8"       Текущее здоровье: " +
            std::to_string(static_cast<int>(player.current_health_)) + "/" +
            std::to_string(static_cast<int>(player.max_health_)));
        player.base_reiki_ += avg_power;
        player.current_reiki_ += avg_power;
        player.RecalculateStats();
        TextView::ShowMessage(
            u8"🌀 Максимальное Рэйки увеличено на " +
            std::to_string(static_cast<int>(avg_power)) + "!\n" +
            u8"       Текущее Рэйки: " +
            std::to_string(static_cast<int>(player.current_reiki_)) + "/" +
            std::to_string(static_cast<int>(player.max_reiki_)));

      } else if (blessing.ability == "dark_ascension") {
        player.strength_ += avg_power;
        player.agility_ += avg_power;
        player.spirit_ -= avg_power;
        TextView::ShowMessage(u8"💪 Сила увеличена на " +
                              std::to_string(avg_power) + "!");
        TextView::ShowMessage(u8"🏹 Ловкость увеличена на " +
                              std::to_string(avg_power) + "!");
        TextView::ShowMessage(u8"🧿 Дух уменьшен на " +
                              std::to_string(avg_power) + "!");
        player.RecalculateStats();

      } else if (blessing.ability == "piercing_stare") {
        player.base_health_ -= avg_power;
        player.RecalculateStats();
        if (player.current_health_ > player.max_health_) {
          player.current_health_ = player.max_health_;
        }
        TextView::ShowMessage(
            u8"💔 Максимальное здоровье уменьшено на " +
            std::to_string(static_cast<int>(avg_power)) + "!\n" +
            u8"       Текущее здоровье: " +
            std::to_string(static_cast<int>(player.current_health_)) + "/" +
            std::to_string(static_cast<int>(player.max_health_)));

        player.blade_.min_damage_ += static_cast<int>(avg_power * 0.5);
        player.blade_.max_damage_ += avg_power;
        TextView::ShowMessage(
            u8"🔪 Минимальный урон Меча увеличен на " +
            std::to_string(static_cast<int>(avg_power * 0.5)) + ",\n" +
            u8"       Максимальный урон Меча увеличен на " +
            std::to_string(static_cast<int>(avg_power)) + "!");

        if (player.current_health_ <= 0) {
          player.current_health_ = 1;
        }
      } else if (blessing.ability == "dragon_eye") {
        player.evasion_ += avg_power * 0.01;
        player.blade_.accuracy_ += avg_power * 0.01;
        TextView::ShowMessage(
            u8"🍃/🎯 Увеличены уклонение Игрока и точность Меча на " +
            std::to_string((avg_power)) + "%!");
      }
    }
  }
}

ModifiedPower BlessingSystem::CalculateModifiedPower(const Blessing& blessing,
                                                     const Player& player) {
  double ki_modifier = 1.0 + abs(player.ki_ / 100.0) * 0.5;
  double spirit_modifier = 1.0 + (player.spirit_ / 20.0) * 0.3;
  double blade_modifier = 1.0 + (player.blade_.spirit_capacity_ / 20.0) * 0.2;
  double total_modifier = ki_modifier * spirit_modifier * blade_modifier;

  return {
      static_cast<int>(blessing.base_power * total_modifier * 0.9),  // min
      static_cast<int>(blessing.base_power * total_modifier * 1.1)   // max
  };
}

void BlessingSystem::ExecuteBlessing(const Blessing& blessing, Player& player,
                                     Enemy* enemy) {
  if (!CanUseBlessing(blessing, player)) {
    TextView::ShowMessage(
        u8"🌀 Недостаточно Рэйки для использования благословения!");
    return;
  }

  if (blessing.type == BlessingType::kActive) {
    player.current_reiki_ -= blessing.reiki_cost;
  }

  ModifiedPower power = CalculateModifiedPower(blessing, player);

  TextView::ShowMessage(u8"✨ Используется благословение: " + blessing.name);

  auto it = BlessingAbilityHandler::ability_map_.find(blessing.ability);
  if (it != BlessingAbilityHandler::ability_map_.end()) {
    it->second(player, enemy, power.min, power.max);
  } else {
    TextView::ShowMessage(u8"⚠️ Неизвестная способность: " + blessing.ability);
  }
}

void BlessingSystem::InitBlessings() {
  BlessingAbilityHandler::InitAbilities();
}
