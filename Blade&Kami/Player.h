#pragma once
#include "KuraiBlade.h"

class Player {
public:
    int level = 1;
    int exp = 0;
    int requiredExp = 100 + 50 * level;
    int ki = 0;
    int strength = 5;
    int agility = 5;
    int spirit = 5;
    double evasion = 0.1;
    double maxHealth = 100.0;
    double currentHealth = 100.0;
    double maxReiki = 50.0;
    double currentReiki = 50.0;
    int availablePoints = 0;
    KuraiBlade blade;

    bool isAlive() const {
        return currentHealth > 0;
    }
    
    void takeDamage(int& damage) {
        currentHealth -= damage;
    }

    void gainExp(int amount) { // Модифицировано
        exp += amount;
        checkLevelUp();
    }

    void checkLevelUp() {
        while (exp >= requiredExp) {
            exp -= requiredExp;
            level++;
            availablePoints += 2;
            requiredExp = 100 + 50 * level;
            // Можно добавить TextView::showMessage("Уровень повышен!");
        }
    }
    void increaseStat(int statType) {
        if (availablePoints <= 0) return;

        switch (statType) {
        case 1: strength++; break;
        case 2: agility++; break;
        case 3: spirit++; break;
        }
        availablePoints--;
    }

	void heal(double amount) {
		currentHealth += amount;
		if (currentHealth > maxHealth) {
			currentHealth = maxHealth;
		}
	}
    void changeKi(int delta) {
        ki += delta;
        if (ki > 100) ki = 100;
        if (ki < -100) ki = -100;
    }
};
