// Enemy.cpp
#include "Enemy.h"

Enemy::Enemy(const EnemyData& baseData) : data(baseData) {
    data.currentHealth = data.maxHealth;
}

void Enemy::takeDamage(int damage) {
    data.currentHealth -= damage;
    if (data.currentHealth < 0) data.currentHealth = 0;
}
void Enemy::setHealth(double health) {
	data.currentHealth = health;
	if (data.currentHealth > data.maxHealth) {
		data.currentHealth = data.maxHealth;
	}
}
bool Enemy::isAlive() const {
    return data.currentHealth > 0;
}

void Enemy::reset() {
    data.currentHealth = data.maxHealth;
}