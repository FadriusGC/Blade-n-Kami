#pragma once
#include <Windows.h>

#include <iostream>
bool localise() {
  SetConsoleOutputCP(CP_UTF8);  // ������������� UTF-8 ��� ������
  SetConsoleCP(CP_UTF8);        // UTF-8 ��� �����
  return true;
}
