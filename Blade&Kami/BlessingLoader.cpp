// BlessingLoader.cpp
#include "BlessingLoader.h"
#include <stdexcept>

std::vector<Blessing> BlessingLoader::loadFromFile(const std::string& filename) {
    std::vector<Blessing> blessings;
    std::ifstream file(filename);

    if (!file) {
        throw std::runtime_error("Failed to open blessings file");
    }

    std::string line;
    std::string currentId;
    std::string name, desc, ability, kami, kamiType;
    BlessingType type = BlessingType::PASSIVE;
    int basePower = 0, reikiCost = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line[0] == '[') {
            // Сохраняем предыдущее благословение
            if (!currentId.empty()) {
                blessings.emplace_back(currentId, name, desc, kami, kamiType, type, ability, basePower, reikiCost);
            }

            // Начинаем новое благословение
            currentId = line.substr(1, line.find(']') - 1);
            name.clear();
            desc.clear();
            kami.clear();
            kamiType.clear();
            ability.clear();
            type = BlessingType::PASSIVE;
            basePower = 0;
            reikiCost = 0;
        }
        else if (line.find("name=") == 0) {
            name = line.substr(5);
        }
        else if (line.find("description=") == 0) {
            desc = line.substr(12);
        }
        else if (line.find("kami=") == 0) {
            kami = line.substr(5);
        }
        else if (line.find("kamiType=") == 0) {
            kamiType = line.substr(9);
        }
        else if (line.find("type=") == 0) {
            std::string typeStr = line.substr(5);
            type = (typeStr == "active") ? BlessingType::ACTIVE : BlessingType::PASSIVE;
        }
        else if (line.find("ability=") == 0) {
            ability = line.substr(8);
        }
        else if (line.find("basePower=") == 0) {
            basePower = std::stoi(line.substr(10));
        }
        else if (line.find("reikiCost=") == 0) {
            reikiCost = std::stoi(line.substr(10));
        }
    }

    // Сохраняем последнее благословение
    if (!currentId.empty()) {
        blessings.emplace_back(currentId, name, desc, kami, kamiType, type, ability, basePower, reikiCost);
    }

    return blessings;
}