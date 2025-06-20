#include "location.h"

Location::Location(int id, const std::string& name, const std::string& desc,
                   const std::string& detailed_desc,
                   const std::vector<int>& conn, const std::string& enemy_id,
                   const std::string& object_id)
    : id_(id),
      name_(name),
      description_(desc),
      detailed_description_(detailed_desc),
      connections_(conn),
      enemy_id_(enemy_id),
      object_id_(object_id),
      object_used_(false) {}
