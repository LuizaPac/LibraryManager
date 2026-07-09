#include "author.h"

namespace library_system {

Author::Author(const int _id, const std::string _name) : id(_id), name(_name) {}

std::string Author::get_name() { return name; }

int Author::get_id() { return id; }

} // namespace library_system
