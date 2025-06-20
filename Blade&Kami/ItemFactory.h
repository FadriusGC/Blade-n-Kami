// ItemFactory.h
#pragma once
#include <stdexcept>
#include <string>

#include "GameState.h"
#include "Item.h"
// ��������������� ����������, ��� �����, ��� include, ������ ��� ����� ��������
// ��� ���������� ���������� � �������? �� � ���� ��� ����� ���� ����� ������,
// ������� ����� ���� ������� ������
// class GameState;

class ItemFactory {
 public:
  static Item createItem(const GameState& state, const std::string& itemId);
};
