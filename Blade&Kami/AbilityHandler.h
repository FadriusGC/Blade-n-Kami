// AbilityHandler.h
#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include <map>
#include <functional>

class AbilityHandler {
public:
    using AbilityFunc = std::function<void(Player&, Enemy*, int, int)>;

    static void initAbilities();
    static void execute(const Item& item, Player& player, Enemy* enemy = nullptr);
    static std::map<std::string, AbilityFunc> abilityMap;

    // Реализации способностей
    static void damage(Player& p, Enemy* e, int min, int max);
    static void heal(Player& p, Enemy* e, int min, int max);
};