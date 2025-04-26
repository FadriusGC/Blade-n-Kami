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
    std::cout << u8"\n=== ������� ���� ===\n"
        << u8"1. ����� ����\n"
        << u8"2. ��������� ����\n"
        << u8"3. �����\n"
        << u8"�������� �������: ";
}

void TextView::showGameMenu() {
    std::cout << u8"\n=== ������� ���� ===\n"
        << u8"1. ������������\n"
        << u8"2. ����� ������\n"
        << u8"3. ��������� ����\n"
        << u8"4. ������� ����\n"
        << u8"�������� ��������: ";
}

void TextView::showMessage(const std::string& msg) {
    std::cout << u8"\n[!] " << msg << "\n";
}
void TextView::showLocation(const Location& loc) {
    std::cout << u8"\n=== " << loc.name << " ===\n"
        << loc.description << "\n\n";
}

void TextView::showAvailableConnections(const GameState& state) {
    std::cout << u8"��������� ��������:\n";
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
    std::cout << u8"\n=== �������������� ������ ===\n"
        << u8"�������: " << player.level << "\n"
        << u8"��������: " << player.currentHealth << "/" << player.maxHealth << "\n"
        << u8"�����: " << player.currentReiki << "/" << player.maxReiki << "\n"
        << u8"����: " << player.strength << "\n"
        << u8"��������: " << player.agility << "\n"
        << u8"���: " << player.spirit << "\n"
        << u8"[1] �������� ����\n[2] �������� ���\n[3] �������� ����� �����\n[0] �����\n�����: ";
}

void TextView::showKuraiMenu(const KuraiBlade& blade) {
    std::cout << u8"\n=== ��� ����� ===\n"
        << u8"����: " << blade.minDamage << "-" << blade.maxDamage << "\n"
        << u8"��������: " << blade.accuracy << "\n"
        << u8"����: " << blade.critChance << "\n"
        << u8"[1] �������� ����\n[2] �������� ��������\n[0] �����\n�����: ";
}

void TextView::showEnemyInfo(const Enemy& enemy) {
    std::cout << "\n=== " << enemy.data.name << " ===\n"
        << u8"��������: " << enemy.data.currentHealth << "/" << enemy.data.maxHealth << "\n"
        << u8"����: " << enemy.data.minDamage << "-" << enemy.data.maxDamage << "\n"
        << u8"�������: " << enemy.data.level << "\n";
}

void TextView::showEnemyList(const std::vector<EnemyData>& enemies) {
    std::cout << u8"\n=== ����������� ����� ===";
    for (const auto& e : enemies) {
        std::cout << "\n[" << e.id << "] " << e.name
            << u8" (�������: " << e.level << ")";
    }
    std::cout << "\n";
}

void TextView::showEnemyDetails(const Enemy& enemy) {
    const auto& d = enemy.data;
    std::cout << "\n=== " << d.name << " ===\n"
        << u8"ID: " << d.id << "\n"
        << u8"�������: " << d.level << "\n"
        << u8"��������: " << d.currentHealth << "/" << d.maxHealth << "\n"
        << u8"����: " << d.minDamage << "-" << d.maxDamage << "\n"
        << u8"��������: " << d.accuracy * 100 << "%\n"
        << u8"���: " << d.spirit << "\n"
        << u8"����: " << d.strength << "\n"
        << u8"�����������: ";
    for (const auto& a : d.abilities) {
        std::cout << a << " ";
    }
    std::cout << "\n";
}