// ItemFactory.h
#pragma once
#include "Item.h"
#include "GameState.h"

class ItemFactory {
public:
    static Item createItem(const GameState& state, const std::string& itemId) {
        for (const auto& itemTemplate : state.itemTemplates) {
            if (itemTemplate.id == itemId) {
                return itemTemplate; // Возвращаем копию шаблона
            }
        }
        throw std::runtime_error("Item template '" + itemId + "' not found");
    }
};
