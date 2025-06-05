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
        
        // �������� ������ �� ������������
        if (!std::getline(std::cin, input)) {
            std::cin.clear();
            TextView::showMessage(u8"������ �����.���������� �����.");
            firstAttempt = false;
            continue;
        }
        if (!firstAttempt && redrawCallback) {
            //std::cin.ignore();
            TextView::clearScreen();
            redrawCallback(); // �������� ������� �����������
        }
        // ���������, �� ������ �� ������
        if (input.empty()) {
            //std::cout << u8"\n����������, ������� �����.\n�������� �������: ";
            TextView::showMessage(u8"����������, ������� �����.\n�������� �������: ");
            firstAttempt = false;
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
           // std::cin.ignore();
            firstAttempt = false;
        }
        catch (const std::invalid_argument&) {
            //std::cout << u8"\n������������ ����. ����������, ������� ������ �����.\n�������� �������: ";
            TextView::showMessage(u8"������������ ����. ����������, ������� ������ �����.\n�������� �������: ");
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
        TextView::showMessage(u8"����������, ������� �����.");
        return 0;
    }*/
    try {
        //if (input.empty()) {
        //    throw kEmpyException(); // ���������� ��� ������� �����
        //}
        
        int choice = std::stoi(input);
        
	    //throw kEmpyException; // ���������� ��� ������� �����
        return choice;
    }
    /*catch (const kEmpyException& e) {
		TextView::showMessage(u8"����������, ������� �����.");
    }*/
    catch (...) {
        TextView::showMessage(u8"������ �����!");
    }
}