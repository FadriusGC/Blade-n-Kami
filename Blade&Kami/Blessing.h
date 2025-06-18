#pragma once
#include <string>

enum class BlessingType {
    ACTIVE,   // ������� ��������� � ���
    PASSIVE   // ���������� ������
};

struct Blessing {
    std::string id;
    std::string name;
    std::string description;
    BlessingType type;
    std::string ability;     // �������� ����������� ��� AbilityHandler
    int basePower;          // ������� ���� (�������������� ��/�����)
    int reikiCost;          // ��������� � ����� (0 ��� ���������)

    Blessing() = default;

    Blessing(const std::string& id, const std::string& name,
        const std::string& desc, BlessingType type,
        const std::string& ability, int basePower, int reikiCost)
        : id(id), name(name), description(desc), type(type),
        ability(ability), basePower(basePower), reikiCost(reikiCost) {}
};
