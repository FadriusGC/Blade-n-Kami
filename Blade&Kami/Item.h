// Item.h
#pragma once
#include <string>

struct Item {
    std::string id;         // ���������� ������������� (��������, "bomb")
    std::string name;       // �������� ��� ����������� ("��������")
    std::string desc;       // �������� ("������� �������� ����")
    int cost;               // ���� � ��������
    std::string ability;    // ��� ����������� ("damage")
    int minPower;           // ����������� �������� (20)
    int maxPower;           // ������������ �������� (30)

    // ����������� �� ���������
    Item() = default;

    // ����������������� �����������
    Item(const std::string& id, const std::string& name,
        const std::string& desc, int cost,
        const std::string& ability, int minP, int maxP)
        : id(id), name(name), desc(desc), cost(cost),
        ability(ability), minPower(minP), maxPower(maxP) {}
};