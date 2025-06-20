#ifndef ITEM_FACTORY_H_
#define ITEM_FACTORY_H_

#include <stdexcept>
#include <string>

#include "game_state.h"
#include "item.h"
// ��������������� ����������, ��� �����, ��� include, ������ ��� ����� ��������
// ��� ���������� ���������� � �������? �� � ���� ��� ����� ���� ����� ������,
// ������� ����� ���� ������� ������
// class GameState;

class ItemFactory {
 public:
  static Item CreateItem(const GameState& state, const std::string& item_id);
};

#endif  // ITEM_FACTORY_H_
