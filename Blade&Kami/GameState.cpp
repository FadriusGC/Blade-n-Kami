#include "GameState.h"
#include "LocationLoader.h"

void GameState::initialize(const std::string& locationsFile) {
    locations = LocationLoader::loadFromFile(locationsFile);
    if (!locations.empty()) {
        currentLocation = &locations[0];
    }
    else {
        throw std::runtime_error("No locations loaded");
    }
}