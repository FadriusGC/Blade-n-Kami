#include "ability_handler.h"

#include "text_view.h"

std::map<std::string, AbilityHandler::AbilityFunc> AbilityHandler::AbilityMap_;
std::mt19937 AbilityHandler::gen_(std::random_device{}());

void AbilityHandler::InitAbilities() {
  AbilityMap_["damage"] = &Damage;
  AbilityMap_["heal"] = &Heal;
}

void AbilityHandler::Execute(const Item& item, Player& player, Enemy* enemy) {
  auto it = AbilityMap_.find(item.ability);
  if (it == AbilityMap_.end()) {
    TextView::ShowMessage(u8"Неизвестная способность: " + item.ability);
    return;
  }

  // Проверка контекста для способностей, требующих врага
  if (item.ability == "damage" && !enemy) {
    TextView::ShowMessage(u8"Нет цели для атаки!");
    return;
  }

  it->second(player, enemy, item.min_power, item.max_power);
}

void AbilityHandler::Damage(Player& player, Enemy* enemy, int min, int max) {
  std::uniform_int_distribution<> dis(min, max);
  int damage = dis(gen_);
  enemy->TakeDamage(damage);
  TextView::ShowMessage(u8"🗡️ Нанесено " + std::to_string(damage) +
                        u8" урона!");
}

void AbilityHandler::Heal(Player& player, Enemy* enemy, int min, int max) {
  std::uniform_int_distribution<> dis(min, max);
  int health_value = dis(gen_);
  player.Heal(health_value);
  TextView::ShowMessage(u8"💚 Восстановлено " + std::to_string(health_value) +
                        u8" здоровья!");
}
