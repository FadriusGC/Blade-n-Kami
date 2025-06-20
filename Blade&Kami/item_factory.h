#ifndef ITEM_FACTORY_H_
#define ITEM_FACTORY_H_

#include <stdexcept>
#include <string>

#include "game_state.h"
#include "item.h"
// Предварительное объявление, это лучше, чем include, потому что зачем включать
// все содержимое геймстейта в фектори? Но у меня уже везде было через инклюд,
// поэтому здесь тоже оставлю инклюд
// class GameState;

class ItemFactory {
 public:
  static Item CreateItem(const GameState& state, const std::string& item_id);
};

#endif  // ITEM_FACTORY_H_
