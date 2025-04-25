#pragma once
#include "KuraiBlade.h"

enum class PlayerStatType { STRENGTH, AGILITY, SPIRIT };

class Player {
public:
    int level = 1;
    int exp = 0;
    int strength = 10;
    int agility = 10;
    int spirit = 10;
    double evasion = 0.1;
    double maxHealth = 100.0;
    double currentHealth = 100.0;
    double maxReiki = 50.0;
    double currentReiki = 50.0;
    KuraiBlade blade;

    void upgradeStat(PlayerStatType stat);
    void takeDamage(double damage);
    void heal(double amount);
    void levelUp();
    void updateKi(int delta);
};
