#include "item_factory.h"

#include "game_state.h"

Item ItemFactory::CreateItem(const GameState& state,
                             const std::string& item_id) {
  for (const Item& item : state.item_templates_) {
    if (item.id == item_id) {
      return item;
    }
  }
  throw std::runtime_error("Item template '" + item_id + "' not found");
}
