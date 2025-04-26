#include "GameState.h"
#include "LocationLoader.h"
#include "EnemyLoader.h"

void GameState::initialize(const std::string& locationsFile, const std::string& enemiesFile) {
    locations = LocationLoader::loadFromFile(locationsFile);
    if (!locations.empty()) {
        currentLocation = &locations[0];
    }
    else {
        throw std::runtime_error("No locations loaded");
    }
    enemyTemplates = EnemyLoader::loadFromFile(enemiesFile);
}