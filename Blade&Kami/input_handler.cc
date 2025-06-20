#include "input_handler.h"

#include <iostream>
#include <string>

#include "text_view.h"

int InputHandler::GetInput() {
  std::string input;
  std::cin >> input;
  try {
    int choice = std::stoi(input);
    return choice;
  } catch (...) {
    TextView::ShowMessage(u8"Ошибка ввода!");
  }
}
