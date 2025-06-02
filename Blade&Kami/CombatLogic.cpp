// CombatLogic.cpp
#include "CombatLogic.h"
#include "TextView.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <cmath>
float clamp(float value, float min, float max) {
	return std::max(min, std::min(value, max));
}
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

double CombatLogic::calculatePurificationChance(Player& player, Enemy& enemy) {
    double healthFactor = (1 - (enemy.data.currentHealth) / enemy.data.maxHealth);
	//std::cout << player.spirit << " " << player.blade.spiritCapacity << " " << enemy.data.spirit << std::endl; // Отладочная информация
    double playerTotal = ((player.spirit / 20.0) * 0.5 + ((player.blade.spiritCapacity / 20.0) * 0.5));
   // std::cout << u8"player total: " << playerTotal << std::endl;
    double spiritRatio = (playerTotal / (enemy.data.spirit));
   // std::cout << spiritRatio << spiritRatio * 0.4 << healthFactor << healthFactor * 0.6 << std::endl;
    double result = spiritRatio * 0.4 + healthFactor * 0.6; 
    return result;
	
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
    else if (action == 2) {
     //purification
        float purificationChance = calculatePurificationChance(player, enemy);
		std::uniform_real_distribution<> dis(0.0, 1.0);
		if (dis(gen) <= purificationChance) {
			enemy.setHealth(0);
			//std::cout << purificationChance << std::endl; otladka
			TextView::showMessage(u8"Вы успешно очистили " + enemy.data.name + u8"!");
		}
		else {
			TextView::showMessage(u8"Очищение не удалось.");
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

