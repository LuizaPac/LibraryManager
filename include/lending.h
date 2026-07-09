#pragma once

#include "book.h"
#include "date.h"
#include "user.h"

namespace library_system {

class Lending {
public:
  Lending(int, User *, Book *, Date, Date);

  // Get methods
  int getLendingId() const;
  User *getBorrower() const;
  Book *getBorrowedBook() const;
  Date getLendingDate() const;
  Date getReturnDate();
  void setReturnDate(Date);

private:
  int lendingId;
  User *borrower;
  Book *borrowedBook;
  Date lendingDate;
  Date returnDate;
};

} // namespace library_system
