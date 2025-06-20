// Inventory.cpp
#include "Inventory.h"

#include "GameState.h"
#include "ItemFactory.h"

void Inventory::addItem(const std::string& itemId, const GameState& state) {
  Item newItem = ItemFactory::createItem(state, itemId);

  if (newItem.id == "sake_flask") {
    sakeCharges++;
  } else if (newItem.id == "whetstone") {
    whetstones++;
  } else {
    items.push_back(newItem);
  }
}

void Inventory::removeItem(const std::string& itemId) {
  items.erase(
      std::remove_if(items.begin(), items.end(),
                     [&itemId](const Item& item) { return item.id == itemId; }),
      items.end());
}
