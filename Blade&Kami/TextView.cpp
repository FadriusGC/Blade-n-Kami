#pragma once
#include "GameState.h"
#include <iostream>
#include "TextView.h"
#include "MenuSystem.h"
#include "Player.h"

static void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
};


static void showLocation(const Location& loc) {
    std::cout << "\n=== " << loc.name << " ===\n"
        << loc.description << "\n";
};

static void showAvailableConnections(const GameState& state) {
    std::cout << "\n��������� ��������:\n";
    for (int connId : state.currentLocation->connections) {
        for (const auto& loc : state.locations) {
            if (loc.id == connId) {
                std::cout << "[" << loc.id << "] " << loc.name << "\n";
                break;
            }
        }
    }
    std::cout << "������� ID ������� ��� 'b' ��� ��������: ";
};

static void showPlayerStats(const Player& player) {
    clearScreen();
    std::cout << "=== �������������� ��������� ===\n"
        << "�������: " << player.level << "\n"
        << "����: " << player.exp << "/100\n"
        << "����: " << player.strength << "\n"
        << "��������: " << player.agility << "\n"
        << "���: " << player.spirit << "\n"
        << "��������: " << player.currentHealth << "/" << player.maxHealth << "\n"
        << "�����: " << player.currentReiki << "/" << player.maxReiki << "\n"
        << "\n������� ����� ������� ��� ��������...";
};