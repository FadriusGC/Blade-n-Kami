// CombatLogic.cpp
#include "CombatLogic.h"
#include "TextView.h"
#include <random>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "BlessingSystem.h"
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
        int bonusDamage = 0;
        for (const auto& blessing : player.blessings) {
            if (blessing.ability == "damage_boost" && blessing.type == BlessingType::PASSIVE) {
                bonusDamage += BlessingSystem::calculateModifiedPower(blessing, player);
            }
        }
        if (calculateHit(player.blade.accuracy, enemy.data.evasion)) {
            int dmg = calculateDamage(player.blade.minDamage, player.blade.maxDamage);
            enemy.takeDamage(dmg);
            TextView::showMessage(u8"🗡️ Вы нанесли " + std::to_string(dmg) + u8" урона!");
            if (bonusDamage > 0) {
                TextView::showMessage(u8"✨ Ваши Благословения усилили удар на " + std::to_string(bonusDamage) + u8" урона!");
            }
            if (!enemy.isAlive()) {
				CombatLogic::onEnemyKilled(player, enemy);
            }

        }
        else {
            TextView::showMessage(u8"💨 Промах!");
            if (!enemy.isAlive()) {
                CombatLogic::onEnemyKilled(player, enemy);
            }
        }
    }
    else if (action == 2) {
     //purification
        float purificationChance = calculatePurificationChance(player, enemy);
		std::uniform_real_distribution<> dis(0.0, 1.0);
		if (dis(gen) <= purificationChance) {
			enemy.setHealth(0);
			//std::cout << purificationChance << std::endl; otladka
			/*TextView::showMessage(u8"Вы успешно очистили " + enemy.data.name + u8"!");*/
            CombatLogic::onEnemyPurified(player, enemy);
		}
		else {
			TextView::showMessage(u8"🖤 Очищение не удалось.");
		}
    }
    else if (action == 3) {

    }
}

void CombatLogic::processEnemyAction(Player& player, Enemy& enemy) {
    double damageReduction = 0.0;
    for (const auto& blessing : player.blessings) {
        if (blessing.ability == "damage_reduction" && blessing.type == BlessingType::PASSIVE) {
            damageReduction += BlessingSystem::calculateModifiedPower(blessing, player) / 100.0;
        }
    }
    if (calculateHit(enemy.data.accuracy, player.evasion)) {
        int baseDmg = calculateDamage(enemy.data.minDamage, enemy.data.maxDamage);
        int finalDmg = static_cast<int>(baseDmg * (1.0 - damageReduction));
        player.takeDamage(finalDmg);
        TextView::showMessage(u8"🗡️ " + enemy.data.name + u8" наносит " + std::to_string(finalDmg) + u8" урона!");
        if (damageReduction > 0.0) {
            TextView::showMessage(u8"🛡️ Благословение уменьшило урон на " +
                std::to_string(baseDmg - finalDmg) + u8" единиц!");
        }
        std::cin.ignore();

    }
    else {
        TextView::showMessage(u8"💨 " + enemy.data.name + u8" промахнулся!");
        std::cin.ignore();
    }
}

void CombatLogic::onEnemyKilled(Player& player, Enemy& enemy) {
    int kiLoss = 10 + (enemy.data.spirit / 2);
    std::uniform_real_distribution<>randomReward(enemy.data.goldReward - enemy.data.goldReward * 0.2, enemy.data.goldReward * 1.2);
    int goldReward = randomReward(gen);
    player.changeKi(-kiLoss); 
    TextView::showWinMessage(u8"====🏆Победа🏆====\n🌟 Опыт +"
        + std::to_string(enemy.data.expReward) + u8"\n" + u8"💰 Мон Души: +" + std::to_string(goldReward) + u8"\n🌑 Ки изменилось на " + std::to_string(-kiLoss) + u8"\n==================");
    player.gainExp(enemy.data.expReward);
    player.gainGold(goldReward);
}

void  CombatLogic::onEnemyPurified(Player& player, Enemy& enemy) {
    int kiGain = 15 + (enemy.data.spirit / 2);
    std::uniform_real_distribution<>randomReward(enemy.data.goldReward - enemy.data.goldReward * 0.2, enemy.data.goldReward * 1.2);
    int goldReward = randomReward(gen);
    player.changeKi(kiGain);
    TextView::showWinMessage(u8"====🏆Победа🏆====\n🤍 Вы успешно Очистили "+ enemy.data.name + u8"!" + u8"\n🌟 Опыт +"
        + std::to_string(enemy.data.expReward) + u8"\n" + u8"💰 Мон Души: +" + std::to_string(goldReward) + u8"\n🌕 Ки изменилось на +" + std::to_string(kiGain) + u8"\n==================");
    player.gainExp(enemy.data.expReward);
    player.gainGold(goldReward);
}
