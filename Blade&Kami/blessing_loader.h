#ifndef BLESSING_LOADER_H_
#define BLESSING_LOADER_H_

#include <fstream>
#include <string>
#include <vector>

#include "blessing.h"

class BlessingLoader {
 public:
  static std::vector<Blessing> LoadFromFile(const std::string& filename);
};

#endif  // BLESSING_LOADER_H_
