#include "GameState.h"
#include "LocationLoader.h"
#include "EnemyLoader.h"

void GameState::initialize(const std::string& locationsFile, const std::string& enemiesFile, const std::string& itemsFile) {
    locations = LocationLoader::loadFromFile(locationsFile);
    if (!locations.empty()) {
        currentLocation = &locations[0];
    }
    else {
        throw std::runtime_error("No locations loaded");
    }
    enemyTemplates = EnemyLoader::loadFromFile(enemiesFile);
    itemTemplates = ItemLoader::loadFromFile(itemsFile);
    itemTemplates.emplace_back("sake_flask", "Фляга Сакэ",
        "Восстанавливает здоровье", 0, "heal", 30, 30);
    itemTemplates.emplace_back("whetstone", "Точильный Камень",
        "Улучшает меч", 0, "upgrade", 1, 1);
}