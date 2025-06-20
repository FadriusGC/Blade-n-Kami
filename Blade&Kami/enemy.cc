#include "enemy.h"

Enemy::Enemy(const EnemyData& base_data) : data_(base_data) {
  data_.current_health = data_.max_health;
}

void Enemy::TakeDamage(int damage) {
  data_.current_health -= damage;
  if (data_.current_health < 0) data_.current_health = 0;
}
void Enemy::SetHealth(double health) {
  data_.current_health = health;
  if (data_.current_health > data_.max_health) {
    data_.current_health = data_.max_health;
  }
}
bool Enemy::IsAlive() const { return data_.current_health > 0; }

void Enemy::Reset() { data_.current_health = data_.max_health; }
