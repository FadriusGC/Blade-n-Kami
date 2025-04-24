#pragma once
#include <vector>
#include <string>

class Location {
public:
    int id;
    std::string name;
    std::string description;
    std::vector<int> connections;

    Location(int id, const std::string& name, const std::string& desc, const std::vector<int>& conn);
};