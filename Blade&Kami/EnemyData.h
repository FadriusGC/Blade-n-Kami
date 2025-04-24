
#pragma once
#include <vector>
#include <string>

struct Spell {
    std::string name; //������ ���������
    float power;
    int cost;
};

struct EnemyData {
    std::string id;
    int strength;
    int agility;
    int spirit;
    float evasion;
    float accuracy;
    int minDamage;
    int maxDamage;
    float maxHealth;
    std::vector<Spell> spells;
};