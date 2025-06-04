#include "InputHandler.h"
#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include "TextView.h"
int InputHandler::getIntInput() {
    int result;
    std::string input;
    while (true) {
        // Получаем строку от пользователя
        if (!std::getline(std::cin, input)) {
            // Если произошла ошибка чтения (например, EOF)
            std::cin.clear();
            //std::cout << u8"\nОшибка ввода. Попробуйте снова.\n";
            TextView::showMessage(u8"Ошибка ввода.Попробуйте снова.");
            continue;
        }

        // Проверяем, не пустая ли строка
        if (input.empty()) {
            //std::cout << u8"\nПожалуйста, введите число.\nВыберите вариант: ";
            TextView::showMessage(u8"Пожалуйста, введите число.\nВыберите вариант: ");
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
        }
        catch (const std::invalid_argument&) {
            //std::cout << u8"\nНекорректный ввод. Пожалуйста, введите только цифры.\nВыберите вариант: ";
            TextView::showMessage(u8"Некорректный ввод. Пожалуйста, введите только цифры.\nВыберите вариант: ");
        }
    }

    return result;
}