// Item.h
#pragma once
#include <string>

struct Item {
    std::string id;         // Уникальный идентификатор (например, "bomb")
    std::string name;       // Название для отображения ("Бомбочка")
    std::string desc;       // Описание ("Наносит взрывной урон")
    int cost;               // Цена в магазине
    std::string ability;    // Тип способности ("damage")
    int minPower;           // Минимальная мощность (20)
    int maxPower;           // Максимальная мощность (30)

    // Конструктор по умолчанию
    Item() = default;

    // Параметризованный конструктор
    Item(const std::string& id, const std::string& name,
        const std::string& desc, int cost,
        const std::string& ability, int minP, int maxP)
        : id(id), name(name), desc(desc), cost(cost),
        ability(ability), minPower(minP), maxPower(maxP) {}
};