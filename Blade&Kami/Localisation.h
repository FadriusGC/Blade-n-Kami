#ifndef LOCALISATION_H_
#define LOCALISATION_H_

#include <Windows.h>

#include <iostream>
bool Localise() {
  SetConsoleOutputCP(CP_UTF8);  // Устанавливаем UTF-8 для вывода
  SetConsoleCP(CP_UTF8);        // UTF-8 для ввода
  return true;
}

#endif  // LOCALISATION_H_
