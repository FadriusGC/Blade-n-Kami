#ifndef LOCALISATION_H_
#define LOCALISATION_H_

#include <Windows.h>

#include <iostream>
bool Localise() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  return true;
}

#endif  // LOCALISATION_H_
