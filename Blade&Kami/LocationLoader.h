#pragma once
#include <fstream>
#include <vector>

#include "Location.h"

class LocationLoader {
 public:
  static std::vector<Location> loadFromFile(const std::string& filename);
};
