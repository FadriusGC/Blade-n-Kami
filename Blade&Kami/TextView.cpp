// TextView.cpp
#include "TextView.h"
#include <iostream>
#include <cstdlib>

void TextView::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void TextView::showMainMenu() {
    std::cout << "\n=== ������� ���� ===\n"
        << "1. ����� ����\n"
        << "2. ��������� ����\n"
        << "3. �����\n"
        << "�������� �������: ";
}

void TextView::showGameMenu() {
    std::cout << "\n=== ������� ���� ===\n"
        << "1. ������������\n"
        << "2. ����� ������\n"
        << "3. ��������� ����\n"
        << "4. ������� ����\n"
        << "�������� ��������: ";
}

void TextView::showMessage(const std::string& msg) {
    std::cout << "\n[!] " << msg << "\n";
}
void TextView::showLocation(const Location& loc) {
    std::cout << "\n=== " << loc.name << " ===\n"
        << loc.description << "\n\n";
}

void TextView::showAvailableConnections(const GameState& state) {
    std::cout << "��������� ��������:\n";
    for (int connId : state.currentLocation->connections) {
        for (const auto& loc : state.locations) {
            if (loc.id == connId) {
                std::cout << "[" << loc.id << "] " << loc.name << "\n";
                break;
            }
        }
    }
    //std::cout << "\n������� ID ������� ��� 'q' ��� ������: ";
}