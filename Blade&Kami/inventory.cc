#include "inventory.h"

#include "game_state.h"
#include "item_factory.h"

void Inventory::AddItem(const std::string& item_id, const GameState& state) {
  Item new_item = ItemFactory::CreateItem(state, item_id);

  if (new_item.id == "sake_flask") {
    sake_charges_++;
  } else if (new_item.id == "whetstone") {
    whetstones_++;
  } else {
    items_.push_back(new_item);
  }
}

void Inventory::RemoveItem(const std::string& item_id) {
  items_.erase(std::remove_if(
                   items_.begin(), items_.end(),
                   [&item_id](const Item& item) { return item.id == item_id; }),
               items_.end());
}

void Inventory::Clear() {
  items_.clear();
  whetstones_ = 0;
  sake_charges_ = 0;
}
