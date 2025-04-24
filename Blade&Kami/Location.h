#pragma once
#include <vector>
#include <string>

class Location {
public:
    int id;
    std::string name;
    std::string description;
    std::vector<int> connectedLocations;

    Location(int id, std::string name, std::string desc)
        : id(id), name(name), description(desc) {}
};