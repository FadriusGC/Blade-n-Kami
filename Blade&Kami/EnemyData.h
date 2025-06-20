
#pragma once
#include <string>
#include <vector>

struct Spell {
  std::string name;  // спеллы переделаю
  double power;
  int cost;
};

struct EnemyData {
  std::string id;
  int strength;
  int agility;
  int spirit;
  double evasion;
  double accuracy;
  int minDamage;
  int maxDamage;
  double maxHealth;
  std::vector<Spell> spells;
};
