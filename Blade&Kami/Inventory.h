// Inventory.h
#pragma once
#include <string>
#include <vector>

#include "Item.h"

class GameState;  // Предварительное объявление

class Inventory {
 public:
  std::vector<Item> items;
  int sakeCharges = 2;
  int whetstones = 100;

  void addItem(const std::string& itemId, const GameState& state);
  void removeItem(const std::string& itemId);
};
