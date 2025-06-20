#ifndef INVENTORY_H_
#define INVENTORY_H_

#include <string>
#include <vector>

#include "item.h"

class GameState;  // Предварительное объявление

class Inventory {
 public:
  std::vector<Item> items_;
  int sake_charges_ = 2;
  int whetstones_ = 100;

  void AddItem(const std::string& item_id, const GameState& state);
  void RemoveItem(const std::string& item_id);
};

#endif  // INVENTORY_H_
