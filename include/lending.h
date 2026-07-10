#pragma once

#include "book.h"
#include "date.h"
#include "user.h"

namespace library_system {

class Lending {
public:
  Lending(int, User *, Book *, Date);

  // Get methods
  int getLendingId() const;
  User *getBorrower() const;
  Book *getBorrowedBook() const;
  Date getLendingDate() const;

private:
  int lendingId;
  User *borrower;
  Book *borrowedBook;
  Date lendingDate;
};

} // namespace library_system
