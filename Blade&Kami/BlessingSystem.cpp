#include "BlessingSystem.h"
#include "AbilityHandler.h"
#include "TextView.h"
#include <algorithm>
#include <random>

std::mt19937 BlessingSystem::gen(std::random_device{}());

void BlessingSystem::initBlessings() {
    // Инициализация уже есть в AbilityHandler
    // Можно добавить специфичные для благословений способности
}


std::string BlessingSystem::getKamiType(const Blessing& blessing) {
    if (blessing.kamiType == u8"good") {
        return u8"Свет";
    }
    else if (blessing.kamiType == u8"evil") {
        return u8"Тьма";
    }
}

std::vector<Blessing> BlessingSystem::getRandomBlessings(const std::vector<Blessing>& allBlessings,
    const std::vector<Blessing>& playerBlessings,
    int count) {
    std::vector<Blessing> availableBlessings;

    // Фильтруем благословения, которых нет у игрока
    for (const auto& blessing : allBlessings) {
        bool hasBlessing = false;
        for (const auto& playerBlessing : playerBlessings) {
            if (playerBlessing.id == blessing.id) {
                hasBlessing = true;
                break;
            }
        }
        if (!hasBlessing) {
            availableBlessings.push_back(blessing);
        }
    }

    // Если доступных благословений меньше чем нужно, возвращаем все доступные
    if (availableBlessings.size() <= count) {
        return availableBlessings;
    }

    // Выбираем случайные благословения
    std::vector<Blessing> selectedBlessings;
    std::shuffle(availableBlessings.begin(), availableBlessings.end(), gen);

    for (int i = 0; i < count && i < availableBlessings.size(); ++i) {
        selectedBlessings.push_back(availableBlessings[i]);
    }

    return selectedBlessings;
}

int BlessingSystem::calculateModifiedPower(const Blessing& blessing, const Player& player) {
    // Модификаторы: Ки, Дух игрока, Духовная ёмкость меча
    double kiModifier = 1.0 + abs(player.ki / 100.0) * 0.5;  // Ки влияет на ±50%
    double spiritModifier = 1.0 + (player.spirit / 20.0) * 0.3;  // Дух влияет на +30%
    double bladeModifier = 1.0 + (player.blade.spiritCapacity / 20.0) * 0.2;  // Меч влияет на +20%

    double totalModifier = kiModifier * spiritModifier * bladeModifier;
    return static_cast<int>(blessing.basePower * totalModifier);
}

bool BlessingSystem::canUseBlessing(const Blessing& blessing, const Player& player) {
    if (blessing.type == BlessingType::PASSIVE) {
        return true;  // Пассивные всегда активны
    }

    return player.currentReiki >= blessing.reikiCost;
}

void BlessingSystem::executeBlessing(const Blessing& blessing, Player& player, Enemy* enemy) {
    if (!canUseBlessing(blessing, player)) {
        TextView::showMessage(u8"🌀 Недостаточно Рэйки для использования благословения!");
        return;
    }

    // Тратим Рэйки для активных благословений
    if (blessing.type == BlessingType::ACTIVE) {
        player.currentReiki -= blessing.reikiCost;
    }

    // Вычисляем модифицированную силу
    int modifiedPower = calculateModifiedPower(blessing, player);

    TextView::showMessage(u8"✨ Используется благословение: " + blessing.name);

    // Используем AbilityHandler для выполнения способности
    if (blessing.ability == "heal") {
        AbilityHandler::heal(player, enemy, modifiedPower, modifiedPower);
    }
    else if (blessing.ability == "damage") {
        if (enemy) {
            AbilityHandler::damage(player, enemy, modifiedPower, modifiedPower);
        }
    }
    else if (blessing.ability == "reiki_restore") {
        player.currentReiki += modifiedPower;
        if (player.currentReiki > player.maxReiki) {
            player.currentReiki = player.maxReiki;
        }
        TextView::showMessage(u8"🌀 Восстановлено " + std::to_string(modifiedPower) + u8" Рэйки!");
    }
    else if (blessing.ability == "purification_boost") {
        // Это благословение будет обрабатываться в CombatLogic
        TextView::showMessage(u8"🤍 Сила очищения увеличена!");
    }
}

void BlessingSystem::applyPassiveBlessings(Player& player, const std::vector<Blessing>& blessings) {
    // Применяем пассивные эффекты благословений
    for (const auto& blessing : blessings) {
        if (blessing.type == BlessingType::PASSIVE) {
            int modifiedPower = calculateModifiedPower(blessing, player);

            if (blessing.ability == "health_boost") {
                player.maxHealth += modifiedPower;
                player.currentHealth += modifiedPower;
            }
            else if (blessing.ability == "reiki_boost") {
                player.maxReiki += modifiedPower;
                player.currentReiki += modifiedPower;
            }
            else if (blessing.ability == "strength_boost") {
                player.strength += modifiedPower;
            }
            else if (blessing.ability == "agility_boost") {
                player.agility += modifiedPower;
            }
            else if (blessing.ability == "spirit_boost") {
                player.spirit += modifiedPower;
            }
        }
    }
}