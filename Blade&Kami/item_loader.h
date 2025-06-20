#ifndef ITEMLOADER_H_
#define ITEMLOADER_H_

#include <vector>

#include "item.h"

class ItemLoader {
 public:
  static std::vector<Item> LoadFromFile(const std::string& filename);
};

#endif  // ITEMLOADER_H_
