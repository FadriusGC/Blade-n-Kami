// ItemFactory.h
#pragma once
#include <stdexcept>
#include <string>
#include "Item.h"
// Предварительное объявление
class GameState;

class ItemFactory {
public:
    static Item createItem(const GameState& state, const std::string& itemId);
};