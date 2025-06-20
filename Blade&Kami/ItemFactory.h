// ItemFactory.h
#pragma once
#include <stdexcept>
#include <string>

#include "GameState.h"
#include "Item.h"
// Предварительное объявление, это лучше, чем include, потому что зачем включать
// все содержимое геймстейта в фектори? Но у меня уже везде было через инклюд,
// поэтому здесь тоже оставлю инклюд
// class GameState;

class ItemFactory {
 public:
  static Item createItem(const GameState& state, const std::string& itemId);
};
