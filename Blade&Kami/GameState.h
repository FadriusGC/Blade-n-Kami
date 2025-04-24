#pragma once
#include "Location.h"
#include <vector>

class GameState {
public:
    std::vector<Location> locations;
    Location* currentLocation;

    void initialize(const std::string& locationsFile);
};