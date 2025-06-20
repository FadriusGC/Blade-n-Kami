#ifndef LOCATION_LOADER_H_
#define LOCATION_LOADER_H_

#include <fstream>
#include <vector>

#include "location.h"

class LocationLoader {
 public:
  static std::vector<Location> LoadFromFile(const std::string& filename);
};

#endif  // LOCATION_LOADER_H_
