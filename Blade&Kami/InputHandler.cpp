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
        // �������� ������ �� ������������
        if (!std::getline(std::cin, input)) {
            // ���� ��������� ������ ������ (��������, EOF)
            std::cin.clear();
            //std::cout << u8"\n������ �����. ���������� �����.\n";
            TextView::showMessage(u8"������ �����.���������� �����.");
            continue;
        }

        // ���������, �� ������ �� ������
        if (input.empty()) {
            //std::cout << u8"\n����������, ������� �����.\n�������� �������: ";
            TextView::showMessage(u8"����������, ������� �����.\n�������� �������: ");
            continue;
        }
        try {
            result = std::stoi(input);
            break; // ������� �������� �����
        }
        catch (const std::out_of_range&) {
            std::cout << u8"\n[!]\n����� ������� �������. ���� ��������� ����� �� "
                << std::numeric_limits<int>::min() << u8" �� "
                << std::numeric_limits<int>::max() << u8".\n�� ������� ��������� �����, �������� �� ������������ ���������, ��� ����� ������ ������ �� ������� :)\n�������� �������: ";
        }
        catch (const std::invalid_argument&) {
            //std::cout << u8"\n������������ ����. ����������, ������� ������ �����.\n�������� �������: ";
            TextView::showMessage(u8"������������ ����. ����������, ������� ������ �����.\n�������� �������: ");
        }
    }

    return result;
}