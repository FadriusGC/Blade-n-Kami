// AbilityHandler.cpp
#include "AbilityHandler.h"
#include <random>
#include <iostream>
#include <map>

std::map<std::string, AbilityHandler::AbilityFunc> AbilityHandler::abilityMap;
std::mt19937 gen(std::random_device{}());

void AbilityHandler::initAbilities() {
    abilityMap["damage"] = &damage;
    abilityMap["heal"] = &heal;
}

void AbilityHandler::execute(const Item& item, Player& player, Enemy* enemy) {
    if (abilityMap.count(item.ability)) {
        abilityMap[item.ability](player, enemy, item.minPower, item.maxPower);
    }
}

// Реализации способностей
void AbilityHandler::damage(Player& p, Enemy* e, int min, int max) {
    if (!e) return;
    std::uniform_int_distribution<> dis(min, max);
    e->takeDamage(dis(gen));
}

void AbilityHandler::heal(Player& p, Enemy* e, int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    p.heal(dis(gen));
}