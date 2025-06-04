#pragma once
#include <string>
class InputHandler {
public:
    // Основной метод для получения числового ввода от пользователя
    // Параметры:
    // prompt - сообщение для пользователя (необязательно)
    // clearInputBuffer - нужно ли очищать буфер ввода перед запросом (по умолчанию true)
    static int getIntInput();

private:
    // Вспомогательный метод для очистки cin от некорректного ввода
    static void clearInputStream();

    // Проверка, является ли строка валидным целым числом
    static bool isValidInteger(const std::string& str);
};