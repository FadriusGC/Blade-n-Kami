#pragma once

#include <vector>
#include <string>

struct LocationObject {
    std::string type;  // "enemy", "chest", "trap"
    std::string id;
};

struct LocationData {
    int id;
    std::string name;
    std::string description;
    std::vector<LocationObject> objects;
    std::vector<int> connectedLocations;
};