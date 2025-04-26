// Enemy.cpp
#include "Enemy.h"

Enemy::Enemy(const EnemyData& baseData) : data(baseData) {
    data.currentHealth = data.maxHealth;
}

void Enemy::takeDamage(double damage) {
    data.currentHealth -= damage;
    if (data.currentHealth < 0) data.currentHealth = 0;
}

bool Enemy::isAlive() const {
    return data.currentHealth > 0;
}

void Enemy::reset() {
    data.currentHealth = data.maxHealth;
}