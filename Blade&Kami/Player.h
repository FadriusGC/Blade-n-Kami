#pragma once
#include "KuraiBlade.h"

class Player {
public:
    int level = 1;
    int exp = 0;
    int requiredExp = 100 + 50 * level;
    int strength = 10;
    int agility = 10;
    int spirit = 10;
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

    void gainExp(int amount) { // ��������������
        exp += amount;
        checkLevelUp();
    }

    void checkLevelUp() {
        while (exp >= requiredExp) {
            exp -= requiredExp;
            level++;
            availablePoints += 2;
            requiredExp = 100 + 50 * level;
            // ����� �������� TextView::showMessage("������� �������!");
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
    }
    void updateKi(int delta);
};
