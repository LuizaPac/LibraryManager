#pragma once

#include <string>

namespace library_system {

class Author {
public:
  Author(const int, const std::string);
  // getters
  std::string get_name();
  int get_id();

private:
  int id;
  std::string name;
};

} // namespace library_system
