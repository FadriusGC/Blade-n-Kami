// ItemLoader.h
#pragma once
#include <vector>

#include "Item.h"

class ItemLoader {
 public:
  static std::vector<Item> loadFromFile(const std::string& filename);
};
