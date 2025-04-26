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

void TextView::showPlayerMenu(const Player& player) {
    std::cout << "\n=== �������������� ������ ===\n"
        << "�������: " << player.level << "\n"
        << "��������: " << player.currentHealth << "/" << player.maxHealth << "\n"
        << "�����: " << player.currentReiki << "/" << player.maxReiki << "\n"
        << "����: " << player.strength << "\n"
        << "��������: " << player.agility << "\n"
        << "���: " << player.spirit << "\n"
        << "[1] �������� ����\n[2] �������� ���\n[3] �������� ����� �����\n[0] �����\n�����: ";
}

void TextView::showKuraiMenu(const KuraiBlade& blade) {
    std::cout << "\n=== ��� ����� ===\n"
        << "����: " << blade.minDamage << "-" << blade.maxDamage << "\n"
        << "��������: " << blade.accuracy << "\n"
        << "����: " << blade.critChance << "\n"
        << "[1] �������� ����\n[2] �������� ��������\n[0] �����\n�����: ";
}

void TextView::showEnemyInfo(const Enemy& enemy) {
    std::cout << "\n=== " << enemy.data.name << " ===\n"
        << "��������: " << enemy.data.currentHealth << "/" << enemy.data.maxHealth << "\n"
        << "����: " << enemy.data.minDamage << "-" << enemy.data.maxDamage << "\n"
        << "�������: " << enemy.data.level << "\n";
}

void TextView::showEnemyList(const std::vector<EnemyData>& enemies) {
    std::cout << "\n=== ����������� ����� ===";
    for (const auto& e : enemies) {
        std::cout << "\n[" << e.id << "] " << e.name
            << " (�������: " << e.level << ")";
    }
    std::cout << "\n";
}

void TextView::showEnemyDetails(const Enemy& enemy) {
    const auto& d = enemy.data;
    std::cout << "\n=== " << d.name << " ===\n"
        << "ID: " << d.id << "\n"
        << "�������: " << d.level << "\n"
        << "��������: " << d.currentHealth << "/" << d.maxHealth << "\n"
        << "����: " << d.minDamage << "-" << d.maxDamage << "\n"
        << "��������: " << d.accuracy * 100 << "%\n"
        << "���: " << d.spirit << "\n"
        << "����: " << d.strength << "\n"
        << "�����������: ";
    for (const auto& a : d.abilities) {
        std::cout << a << " ";
    }
    std::cout << "\n";
}