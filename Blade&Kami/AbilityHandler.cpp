// AbilityHandler.cpp
#include "AbilityHandler.h"
#include "TextView.h"

std::map<std::string, AbilityHandler::AbilityFunc> AbilityHandler::abilityMap;
std::mt19937 AbilityHandler::gen(std::random_device{}());

void AbilityHandler::initAbilities() {
    abilityMap["damage"] = &damage;
    abilityMap["heal"] = &heal;


}

void AbilityHandler::execute(const Item& item, Player& player, Enemy* enemy) {
    auto it = abilityMap.find(item.ability);
    if (it == abilityMap.end()) {
        TextView::showMessage(u8"Неизвестная способность: " + item.ability);
        return;
    }

    // Проверка контекста для способностей, требующих врага
    if (item.ability == "damage" && !enemy) {
        TextView::showMessage(u8"Нет цели для атаки!");
        return;
    }

    it->second(player, enemy, item.minPower, item.maxPower);
}

void AbilityHandler::damage(Player& p, Enemy* e, int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    int damage = dis(gen);
    e->takeDamage(damage);
    TextView::showMessage(u8"🗡️ Нанесено " + std::to_string(damage) + u8" урона!");
}

void AbilityHandler::heal(Player& p, Enemy* e, int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    int healValue = dis(gen);
    p.heal(healValue);
    TextView::showMessage(u8"💚 Восстановлено " + std::to_string(healValue) + u8" здоровья!");
}