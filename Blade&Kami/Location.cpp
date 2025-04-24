#include "Location.h"

Location::Location(int id, const std::string& name, const std::string& desc, const std::vector<int>& conn)
    : id(id), name(name), description(desc), connections(conn) {}