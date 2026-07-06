#pragma once

#include "book.h"
#include "date.h"
#include "document.h"
#include "telephone.h"
#include "user.h"
#include <string>
#include <vector>
#include <pybind11/embed.h>

namespace library_system {

class Library {
public:
  Library(const std::string);

  ~Library();

  int newUser(std::string, Document, Date, Telephone, std::string);

  void userInfo(Document);

  int newBook(std::string, Date, std::string, std::string);

  void bookInfo(int);

  int bookCheckOut(Document, int);

  int bookCheckIn(Document, int);

  void bookStatus(int);

private:
  std::string libraryName;
  std::vector<User *> users;
  std::vector<Book *> books;
  pybind11::scoped_interpreter interpreter;
};

} // namespace library_system
