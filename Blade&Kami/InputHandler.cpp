#include "InputHandler.h"
#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include "TextView.h"
int InputHandler::getIntInput(std::function<void()> redrawCallback) {
    int result;
    std::string input;
    bool firstAttempt = true;


    while (true) {
        
        // Получаем строку от пользователя
        if (!std::getline(std::cin, input)) {
            std::cin.clear();
            TextView::showMessage(u8"Ошибка ввода.Попробуйте снова.");
            firstAttempt = false;
            continue;
        }
        if (!firstAttempt && redrawCallback) {
            //std::cin.ignore();
            TextView::clearScreen();
            redrawCallback(); // Вызываем функцию перерисовки
        }
        // Проверяем, не пустая ли строка
        if (input.empty()) {
            //std::cout << u8"\nПожалуйста, введите число.\nВыберите вариант: ";
            TextView::showMessage(u8"Пожалуйста, введите число.\nВыберите вариант: ");
            firstAttempt = false;
            continue;
        }
        try {
            result = std::stoi(input);
            break; // Успешно получили число
        }
        catch (const std::out_of_range&) {
            std::cout << u8"\n[!]\nЧисло слишком большое. Игра принимает числа от "
                << std::numeric_limits<int>::min() << u8" до "
                << std::numeric_limits<int>::max() << u8".\nНе пытайся вписывать числа, отличные от предложенных вариантов, все равно ничего нового не найдешь :)\nВыберите вариант: ";
           // std::cin.ignore();
            firstAttempt = false;
        }
        catch (const std::invalid_argument&) {
            //std::cout << u8"\nНекорректный ввод. Пожалуйста, введите только цифры.\nВыберите вариант: ";
            TextView::showMessage(u8"Некорректный ввод. Пожалуйста, введите только цифры.\nВыберите вариант: ");
            //std::cin.ignore();
            firstAttempt = false;
        }
        
        //std::cin.ignore();
    }

    return result;
}

int InputHandler::NewInput() {
    std::string input;
    std::cin >> input;
    /*std::getline(std::cin, input);
    if (input.empty()) {
        TextView::showMessage(u8"Пожалуйста, введите число.");
        return 0;
    }*/
    try {
        //if (input.empty()) {
        //    throw kEmpyException(); // Исключение для пустого ввода
        //}
        
        int choice = std::stoi(input);
        
	    //throw kEmpyException; // Исключение для пустого ввода
        return choice;
    }
    /*catch (const kEmpyException& e) {
		TextView::showMessage(u8"Пожалуйста, введите число.");
    }*/
    catch (...) {
        TextView::showMessage(u8"Ошибка ввода!");
    }
}