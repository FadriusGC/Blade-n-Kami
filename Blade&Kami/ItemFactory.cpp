// ItemFactory.cpp
#include "ItemFactory.h"
#include "GameState.h"

Item ItemFactory::createItem(const GameState& state, const std::string& itemId) {
    for (const Item& item : state.itemTemplates) {
        if (item.id == itemId) {
            return item;
        }
    }
    throw std::runtime_error("Item template '" + itemId + "' not found");
}