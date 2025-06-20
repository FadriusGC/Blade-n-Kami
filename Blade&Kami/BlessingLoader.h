#pragma once
#include <fstream>
#include <string>
#include <vector>

#include "Blessing.h"

class BlessingLoader {
 public:
  static std::vector<Blessing> loadFromFile(const std::string& filename);
};
