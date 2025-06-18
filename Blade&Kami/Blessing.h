#pragma once
#include <string>

enum class BlessingType {
    ACTIVE,   // Требует активации в бою
    PASSIVE   // Постоянный эффект
};

struct Blessing {
    std::string id;
    std::string name;
    std::string description;
    BlessingType type;
    std::string ability;     // Название способности для AbilityHandler
    int basePower;          // Базовая сила (модифицируется Ки/Духом)
    int reikiCost;          // Стоимость в Рэйки (0 для пассивных)

    Blessing() = default;

    Blessing(const std::string& id, const std::string& name,
        const std::string& desc, BlessingType type,
        const std::string& ability, int basePower, int reikiCost)
        : id(id), name(name), description(desc), type(type),
        ability(ability), basePower(basePower), reikiCost(reikiCost) {}
};
