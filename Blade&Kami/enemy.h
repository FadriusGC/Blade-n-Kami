#ifndef ENEMY_H_
#define ENEMY_H_

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
  int min_damage = 0;
  int max_damage = 0;
  double max_health = 0;
  double current_health = 0;
  int exp_reward = 0;
  int gold_reward = 0;
  std::vector<std::string> abilities;
};

class Enemy {
 public:
  EnemyData data_;

  Enemy(const EnemyData& base_data);
  void TakeDamage(int damage);
  void SetHealth(double health);
  bool IsAlive() const;
  void Reset();
};

#endif  // ENEMY_H_
