// CombatLogic.cpp
#include "CombatLogic.h"
#include "TextView.h"
#include <random>
#include <iostream>

namespace {
    std::mt19937 gen(std::random_device{}());
}

bool CombatLogic::calculateHit(float acc, float eva) {
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return (dis(gen) <= (acc - eva));
}

int CombatLogic::calculateDamage(int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void CombatLogic::processPlayerAction(Player& player, Enemy& enemy, int action) {
    if (action == 1) { // Атака
        if (calculateHit(player.blade.accuracy, enemy.data.evasion)) {
            int dmg = calculateDamage(player.blade.minDamage, player.blade.maxDamage);
            enemy.takeDamage(dmg);
            TextView::showMessage(u8"Вы нанесли " + std::to_string(dmg) + u8" урона!");
        }
        else {
            TextView::showMessage(u8"Промах!");
        }
    }
}

void CombatLogic::processEnemyAction(Player& player, Enemy& enemy) {
    if (calculateHit(enemy.data.accuracy, player.evasion)) {
        int dmg = calculateDamage(enemy.data.minDamage, enemy.data.maxDamage);
        player.takeDamage(dmg);
        TextView::showMessage(enemy.data.name + u8" наносит " + std::to_string(dmg) + u8" урона!");
        std::cin.ignore();
    }
    else {
        TextView::showMessage(enemy.data.name + u8" промахнулся!");
        std::cin.ignore();
    }
}