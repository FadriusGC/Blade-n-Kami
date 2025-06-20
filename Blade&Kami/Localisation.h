#pragma once
#include <Windows.h>

#include <iostream>
bool localise() {
  SetConsoleOutputCP(CP_UTF8);  // Устанавливаем UTF-8 для вывода
  SetConsoleCP(CP_UTF8);        // UTF-8 для ввода
  return true;
}
