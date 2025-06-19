#pragma once
#include "Blessing.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include <random>

class BlessingSystem {
private:
    static std::mt19937 gen;

public:
    static void initBlessings();

    static std::string getKamiType(const Blessing& blessing);
    static std::vector<Blessing> getRandomBlessings(const std::vector<Blessing>& allBlessings,
        const std::vector<Blessing>& playerBlessings,
        int count = 3);
    static int calculateModifiedPower(const Blessing& blessing, const Player& player);
    static bool canUseBlessing(const Blessing& blessing, const Player& player);
    static void executeBlessing(const Blessing& blessing, Player& player, Enemy* enemy = nullptr);
    static void applyPassiveBlessings(Player& player, const std::vector<Blessing>& blessings);
};
