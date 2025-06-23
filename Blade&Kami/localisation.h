#ifndef LOCALISATION_H_
#define LOCALISATION_H_

#include <Windows.h>

#include <iostream>
bool Localise() {
  SetConsoleOutputCP(CP_UTF8);  // Óñòàíàâëèâàåì UTF-8 äëÿ âûâîäà
  SetConsoleCP(CP_UTF8);        // UTF-8 äëÿ ââîäà
  return true;
}

#endif  // LOCALISATION_H_
