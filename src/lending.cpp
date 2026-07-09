#include "lending.h"
#include "book.h"
#include "date.h"
#include "user.h"

namespace library_system {

Lending::Lending(int lendingId, User *borrower, Book *borrowedBook,
                 Date lendingDate, Date returnDate)
    : lendingId(lendingId), borrower(borrower), borrowedBook(borrowedBook),
      lendingDate(lendingDate) {}

int Lending::getLendingId() const { return lendingId; }
User *Lending::getBorrower() const { return borrower; }
Book *Lending::getBorrowedBook() const { return borrowedBook; }
Date Lending::getLendingDate() const { return lendingDate; }
Date Lending::getReturnDate() { return returnDate; }
void Lending::setReturnDate(Date _date) {
  // alter table
  returnDate = _date;
}

} // namespace library_system
