#pragma once
#include "KuraiBlade.h"
#include "Blessing.h"
#include <vector>


class Player {
public:
    int level = 1;
    int exp = 0;
    int requiredExp = 100 + 50 * level;
    int gold = 0;
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
    std::vector<Blessing> blessings;

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

    void gainGold(int amount) {
        gold += amount;
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
    void restoreReiki(double amount) {
        currentReiki += amount;
        if (currentReiki > maxReiki) {
            currentReiki = maxReiki;
        }
    }
    void changeKi(int delta) {
        ki += delta;
        if (ki > 100) ki = 100;
        if (ki < -100) ki = -100;
    }

    // Методы для работы с благословениями
    void addBlessing(const Blessing& blessing) {
        blessings.push_back(blessing);
    }

    void removeBlessing(const std::string& blessingId) {
        blessings.erase(
            std::remove_if(blessings.begin(), blessings.end(),
                [&blessingId](const Blessing& blessing) {
                    return blessing.id == blessingId;
                }),
            blessings.end()
        );
    }

    bool hasBlessing(const std::string& blessingId) const {
        for (const auto& blessing : blessings) {
            if (blessing.id == blessingId) {
                return true;
            }
        }
        return false;
    }

    std::vector<Blessing> getActiveBlessings() const {
        std::vector<Blessing> activeBlessings;
        for (const auto& blessing : blessings) {
            if (blessing.type == BlessingType::ACTIVE) {
                activeBlessings.push_back(blessing);
            }
        }
        return activeBlessings;
    }

};
