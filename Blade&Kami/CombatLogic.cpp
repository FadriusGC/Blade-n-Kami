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
//todo: ������� ��� �� double ������ float, ����� �� ��������� ��� ������� � �� ���� ������� � ����������� � ����� ����������� �����.
float CombatLogic::calculatePurificationChance(Player& player, Enemy& enemy) { //��� = ((���_� * 2) + Ĩ� / 2) / 100 + (1 - (���_� / ��_�) / 2) * (1 - (���_� * 3) / 100)
    float healthFactor = (1 - (enemy.data.currentHealth) / enemy.data.maxHealth);
	std::cout << player.spirit << " " << player.blade.spiritCapacity << " " << enemy.data.spirit << std::endl; // ���������� ����������
	float playerTotal = ((player.spirit / 20) * 0.5 + ((player.blade.spiritCapacity / 20) * 0.5));
    std::cout << playerTotal << std::endl;// ��� ������ � ����
    float spiritRatio = (playerTotal / (enemy.data.spirit));
    std::cout << spiritRatio << spiritRatio * 0.4 << healthFactor << healthFactor * 0.6 << std::endl;// ��������� ���� ������ � ���� �����
	float result = spiritRatio * 0.4 + healthFactor * 0.6; // 0.4 � 0.6 - ���� ��� ���� � �������� ��������������
    return result;
	//return floor(clamp((((player.spirit * 2) + player.blade.spiritCapacity / 2) / 100 + (1 - ((enemy.data.spirit * 3) / 100)) + (1 - (enemy.data.currentHealth / enemy.data.maxHealth) / 2)), 0.0f, 1.0f));
    //return clamp(((player.spirit * 2) + player.blade.spiritCapacity / 2) / 100 + (1 - (enemy.data.spirit * 3) / 100), 0.0f, 1.0f);
}

void CombatLogic::processPlayerAction(Player& player, Enemy& enemy, int action) {
    if (action == 1) { // �����
        if (calculateHit(player.blade.accuracy, enemy.data.evasion)) {
            int dmg = calculateDamage(player.blade.minDamage, player.blade.maxDamage);
            enemy.takeDamage(dmg);
            TextView::showMessage(u8"�� ������� " + std::to_string(dmg) + u8" �����!");
        }
        else {
            TextView::showMessage(u8"������!");
        }
    }
    else if (action == 2) {
     //purification
        float purificationChance = calculatePurificationChance(player, enemy);
		std::uniform_real_distribution<> dis(0.0, 1.0);
		if (dis(gen) <= purificationChance) {
			enemy.setHealth(0);
			std::cout << purificationChance << std::endl;
			TextView::showMessage(u8"�� ������� �������� " + enemy.data.name + u8"!");
		}
		else {
			TextView::showMessage(u8"�������� �� �������.");
		}
    }
}

void CombatLogic::processEnemyAction(Player& player, Enemy& enemy) {
    if (calculateHit(enemy.data.accuracy, player.evasion)) {
        int dmg = calculateDamage(enemy.data.minDamage, enemy.data.maxDamage);
        player.takeDamage(dmg);
        TextView::showMessage(enemy.data.name + u8" ������� " + std::to_string(dmg) + u8" �����!");
        std::cin.ignore();
    }
    else {
        TextView::showMessage(enemy.data.name + u8" �����������!");
        std::cin.ignore();
    }
}

