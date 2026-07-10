#pragma once

#include "author.h"
#include "book.h"
#include "date.h"
#include "document.h"
#include "genre.h"
#include "lending.h"
#include "telephone.h"
#include "user.h"
#include <pybind11/embed.h>
#include <string>
#include <vector>

namespace library_system {

class Library {
public:
  Library();

  ~Library();

  int newUser(std::string, std::string, Document, Date, Telephone);
  void userInfo(Document);

  int newBook(std::string, Date, std::string, std::string);

  void bookInfo(int);

  int landBook(Document, int);

  void returnBook(Document, int);

  void bookStatus(int);

  void printUsers() const;

  void printBooks() const;

private:
  std::string dateStringFromNow(int daysFromNow = 0) const;
  std::string normalizeDateString(std::string) const;
  Author *findAuthorById(int) const;
  Genre *findGenreById(int) const;
  Genre *findGenreByName(const std::string &) const;

  std::string libraryName;
  std::vector<User *> users;
  std::vector<Book *> books;
  std::vector<Lending *> lendings;
  std::vector<Author *> authors;
  std::vector<Genre *> genres;
  pybind11::scoped_interpreter interpreter;
  pybind11::object authorRepository;
  pybind11::object bookGenreRepository;
  pybind11::object userRepository;
  pybind11::object bookRepository;
  pybind11::object lendingRepository;
};

class CheckInFailed : public std::exception {
public:
  virtual const char *what() const throw() {
    return "ERROR. Something happens in checkin. Try again.";
  }
};

} // namespace library_system
