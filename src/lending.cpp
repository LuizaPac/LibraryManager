#include "lending.h"
#include "book.h"
#include "date.h"
#include "user.h"
#include <ostream>

namespace library_system {

Lending::Lending(int lendingId, User *borrower, Book *borrowedBook,
                 Date lendingDate)
    : lendingId(lendingId), borrower(borrower), borrowedBook(borrowedBook),
      lendingDate(lendingDate) {}

std::ostream &operator<<(std::ostream &output, const Lending &lend) {
  output << "Title: " << lend.getBorrowedBook()->getTitle() << std::endl
         << "    Reader Name: " << lend.getBorrower()->getFirstName() << " "
         << lend.getBorrower()->getLastName() << std::endl
         << "    Reader Document: " << lend.getBorrower()->getDocumentNumber()
         << std::endl
         << "    Lending Date: " << lend.getLendingDate().getStringDate()
         << std::endl;

  return output;
}

int Lending::getLendingId() const { return lendingId; }
User *Lending::getBorrower() const { return borrower; }
Book *Lending::getBorrowedBook() const { return borrowedBook; }
Date Lending::getLendingDate() const { return lendingDate; }

} // namespace library_system
