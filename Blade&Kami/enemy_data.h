#ifndef ENEMYDATA_H_
#define ENEMYDATA_H_

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
  int min_damage;
  int max_damage;
  double max_health;
  std::vector<Spell> spells;
};

#endif  // ENEMYDATA_H_
