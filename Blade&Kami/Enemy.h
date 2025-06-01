// Enemy.h
#pragma once
#include <string>
#include <vector>

struct EnemyData {
    std::string id;
    std::string name;
    int level = 1;
    int strength = 0;
    int agility = 0;
    int spirit = 0;
    double evasion = 0.0;
    double accuracy = 0.0;
    int minDamage = 0;
    int maxDamage = 0;
    double maxHealth = 0;
    double currentHealth = 0;
    int expReward = 0;
    std::vector<std::string> abilities;
};

class Enemy {
public:
    EnemyData data;

    Enemy(const EnemyData& baseData);
    void takeDamage(int damage);
    void setHealth(double health);
    bool isAlive() const;
    void reset();
};