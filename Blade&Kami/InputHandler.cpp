#include "InputHandler.h"
#include <iostream>
#include <string>
#include "TextView.h"

int InputHandler::getInput() {
    std::string input;
    std::cin >> input;
    try {
        int choice = std::stoi(input);
        return choice;
    }
    catch (...) {
        TextView::showMessage(u8"Ошибка ввода!");
    }
}