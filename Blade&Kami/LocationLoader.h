#pragma once
#include "Location.h"
#include <vector>
#include <fstream>

class LocationLoader {
public:
    static std::vector<Location> loadFromFile(const std::string& filename);
};