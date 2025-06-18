#pragma once
#include "Blessing.h"
#include <vector>
#include <string>
#include <fstream>

class BlessingLoader {
public:
    static std::vector<Blessing> loadFromFile(const std::string& filename);
};