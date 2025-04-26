// EnemyLoader.h
#pragma once
#include <vector>
#include "Enemy.h"

class EnemyLoader {
public:
    static std::vector<EnemyData> loadFromFile(const std::string& filename);
};
